//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_GAME_HPP
#define PEDAROGUE_GAME_HPP
#include <memory>
#include "Engine.hpp"


class Game
{
public:
    std::unique_ptr<Engine> mEngine;
    std::vector<Entity> mPlayers;

    void Init();

    Game();

    void run();

    void close();
};


#endif //PEDAROGUE_GAME_HPP
