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
    /**
     * @brief                   move player according to commandType
     * @param commandType       indication of the command given by inputhandler
     */
    void update(CommandType commandType);
};


#endif //PEDAROGUE_PLAYERMOVEMENT_HPP
