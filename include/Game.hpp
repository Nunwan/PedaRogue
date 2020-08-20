//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_GAME_HPP
#define PEDAROGUE_GAME_HPP
#include <memory>
#include "Engine.hpp"
#include "Level.hpp"


class Game
{
private:
    std::vector<std::shared_ptr<Level>> mLevels;

public:
    Game();

    int mPlayerLocalId;
    std::unique_ptr<Engine> mEngine;
    std::vector<Entity> mPlayers;

    /**
     * @brief   Initialize the engine core and the first level : call PlayerCreation at the end
     */
    void Init();

    /**
     * @brief   Create a level and save it in mLevels
     */
    void create_level();

    /**
     * @brief   Create the player of this client with all the components needed
     */
    void PlayerCreation();

    /**
     * @brief       Main game loop
     */
    void run();

    /**
     * @brief       The closing function of the game : last function to be called
     */
    void close();

    // Getters
    const vector<std::shared_ptr<Level>> &getMLevels() const;
};


#endif //PEDAROGUE_GAME_HPP
