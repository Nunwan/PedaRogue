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

    /**
     * @brief                   Do the opposing movement of the previous one in case of collision
     * @param to_move           The entity which has to be moved back
     */
    void go_back(Entity to_move);

};


#endif //PEDAROGUE_PLAYERMOVEMENT_HPP
