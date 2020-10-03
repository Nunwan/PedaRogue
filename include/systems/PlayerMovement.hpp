//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_PLAYERMOVEMENT_HPP
#define PEDAROGUE_PLAYERMOVEMENT_HPP


#include <Window.hpp>
#include "core/ECSTypes.hpp"
#include "Types.hpp"
#include "CommandProcessor.hpp"


class PlayerMovement : public System
{
public:
    /**
     * @brief                   move player according to commandType
     * @param commandType       indication of the command given by inputhandler
     */
    void update();
};

class MovePlayer : public Command
{
private:
    Entity player;
    int direction;
public:
    MovePlayer(Entity player, int direction);

    void execute(Engine* engine) override;

};


#endif //PEDAROGUE_PLAYERMOVEMENT_HPP
