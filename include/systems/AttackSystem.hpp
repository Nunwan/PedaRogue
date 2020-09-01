//
// Created by nunwan on 28/07/2020.
//

#ifndef PEDAROGUE_ATTACKSYSTEM_HPP
#define PEDAROGUE_ATTACKSYSTEM_HPP


#include <core/ECSTypes.hpp>


class AttackSystem : public System
{
public:
    /**
     * @brief           Treat all the attacks in the game at each turn
     */
    void update() override;
};


#endif //PEDAROGUE_ATTACKSYSTEM_HPP
