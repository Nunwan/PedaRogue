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
    int mPlayerLocalId;
    const vector<std::shared_ptr<Level>> &getMLevels() const;
    std::unique_ptr<Engine> mEngine;
    std::vector<Entity> mPlayers;

    void Init();
    void PlayerCreation();

    Game();

    /**
     * @brief       Main game loop
     */
    void run();

    void close();
};


#endif //PEDAROGUE_GAME_HPP
