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
    const vector<std::shared_ptr<Level>> &getMLevels() const;

public:
    std::unique_ptr<Engine> mEngine;
    std::vector<Entity> mPlayers;

    void Init();
    void PlayerCreation();

    Game();

    void run();

    void close();
};


#endif //PEDAROGUE_GAME_HPP
