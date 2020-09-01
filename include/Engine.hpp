//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_ENGINE_HPP
#define PEDAROGUE_ENGINE_HPP
#include <memory>
#include <map>
#include "core/ECSManager.hpp"
#include "Components.hpp"
#include "systems/RenderSystem.hpp"
#include "InputHandler.hpp"
#include "Level.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/FoVCompute.hpp"
#include "systems/LightSystem.hpp"
#include "systems/AttackSystem.hpp"
#include "systems/BackSystem.hpp"
#include "systems/PickSystem.hpp"
#include "Game.hpp"
#include "ProcessEvents.hpp"

enum EventType {
    CollisionEvent,
    NextLevelEvent,
    PreviousLevelEvent
};

struct Event {
    EventType eventtype;
    Entity entity1;
    Entity entity2;
};

class Game;
class Engine : public ECSManager
{
public:
    /**
     * @brief   Systems which have to be updated in update routine
     */
    std::map<std::string, std::shared_ptr<System>> mUpdateSystems;

    /**
     * @brief   Systems which enable the rendering part of the game
     */
    std::map<std::string, std::shared_ptr<System>> mRenderSystems;

    /**
     * @brief   Input handler system which is particular and so does not belong to update or render
     */
    std::shared_ptr<InputHandler> mInputHandler;
    int mNbLvl = 1;
private:
    // All the systems which need to be saved
    std::shared_ptr<Window> mWindow;
    // Callback pointers of game which create the engine
    Game* mGame;

    /**
     * Queue of event cleared and treated each turn in the game loop
     */
    std::queue<Event> mEvents;


public:

    /**
     * @brief       Create the engine, initialize the subroutine and link the engine to a game.
     * @param game  game which creates the engine
     */
    Engine(Game* game);

    // Sub initialisation of the engine
    /**
     * @brief       Initialize all the components needed
     */
    void initComponents();
    /**
     * @brief       Initialize all the system and indicate the components needed for them.
     */
    void initSystems();

    // Main loop subfunction
    /**
     * @brief       Update all the entity to perform a step in the game
     * @return      int which indicated if the game has to stop
     */
    int update();
    /**
     * @brief       Render all the map
     */
    void render();

    // Levels activators
    /**
     * @brief           Activate the level to be displayed
     * @param level     shared_ptr to the level which has to be activate
     */
    void level_enable(std::shared_ptr<Level> level);

    /**
     * @brief           disable the level to be displayed
     * @param level     shared_ptr to the level which has to be desactivated
     */
    void level_disable(std::shared_ptr<Level> level);


    /**
     * @brief           Create a new level randomly
     */
    void create_level();

    // Getters
    /**
     * @brief               Return pointer to the selected level
     * @param levelnumber   level to return
     * @return              shared_ptr to the level
     */
    std::shared_ptr<Level> GetLevel(int levelnumber);


    /**
     * @return              Window class of the game
     */
    const std::shared_ptr<Window> &getMWindow() const;

    /**
     * @return              Return the current player
     */
    Entity& GetPlayer();


    // Systems
    /**
     * @brief               return a shared_ptr to the collision system for the movement system
     */
    std::shared_ptr<CollisionSystem> getCollisionSystem();

    /**
     * @brief                   Return a reference for the entity at the given coordinates
     * @param x                 x coordinate
     * @param y                 y coordinate
     * @param levelnumber       the level where the entity is
     * @return                  The entity at those coordinates
     */
    Entity& getEntityat(int x, int y, int levelnumber);


    // Events
    /**
     * @brief           Push the event in the mEvents queue
     * @param event     Event to be pushed
     */
    void push_Event(Event event);

    /**
     * @brief           Return and delete the next event to be processed in the queue
     * @return          The event to be processed
     */
    Event pop_event();

    /**
     * @brief           Check if there are events to be processed
     * @return          The boolean 1 if there is an event to be processed 0 if not
     */
    bool check_event();
};


#endif //PEDAROGUE_ENGINE_HPP
