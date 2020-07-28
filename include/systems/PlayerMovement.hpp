//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_PLAYERMOVEMENT_HPP
#define PEDAROGUE_PLAYERMOVEMENT_HPP


#include <Window.hpp>
#include "core/ECSTypes.hpp"
#include "Types.hpp"


class PlayerMovement : public System
{
public:
    void update(CommandType commandType);
    void go_back(Entity to_move);

};


#endif //PEDAROGUE_PLAYERMOVEMENT_HPP
