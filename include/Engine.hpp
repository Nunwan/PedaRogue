//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_ENGINE_HPP
#define PEDAROGUE_ENGINE_HPP
#include <memory>
#include "core/ECSManager.hpp"
#include "Components.hpp"
#include "systems/RenderSystem.hpp"
#include "InputHandler.hpp"
#include "Level.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/FoVCompute.hpp"
#include "Game.hpp"

class Game;
class Engine : public ECSManager
{
private:
    std::shared_ptr<Window> mWindow;
    std::shared_ptr<RenderMapSystem> mRenderMapSystem;
    std::shared_ptr<RenderOthersSystem> mRenderOthersSystem;
    std::shared_ptr<InputHandler> mInputHandler;
    std::shared_ptr<FoVCompute> mFovComputeSystem;
    Game* mGame;


public:
    const std::shared_ptr<Window> &getMWindow() const;
    Engine(Game* game);
    void initComponents();
    void initSystems();

    int update();
    void render();

    // Levels activators
    void level_enable(std::shared_ptr<Level> level);
    void level_disable(std::shared_ptr<Level> level);

    std::shared_ptr<CollisionSystem> mCollisionSystem;

    std::shared_ptr<Level> GetLevel(int levelnumber);

    Entity& GetPlayer();
};


#endif //PEDAROGUE_ENGINE_HPP
