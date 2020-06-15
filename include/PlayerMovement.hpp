//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_PLAYERMOVEMENT_HPP
#define PEDAROGUE_PLAYERMOVEMENT_HPP


#include <Window.hpp>
#include "core/ECSTypes.hpp"
#include "core/ECSManager.hpp"
#include "Types.hpp"
#include "Components.hpp"


class PlayerMovement : public System
{
public:
    void update(CommandType commandType);

};


#endif //PEDAROGUE_PLAYERMOVEMENT_HPP
