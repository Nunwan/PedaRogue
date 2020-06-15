//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_GAME_HPP
#define PEDAROGUE_GAME_HPP
#include <memory>
#include "Engine.hpp"


class Game
{
private:
    std::unique_ptr<Engine> mEngine;
    std::vector<Entity> mPlayers;

public:
    void Init();

    Game();

    void run();
};


#endif //PEDAROGUE_GAME_HPP
