//
// Created by nunwan on 28/07/2020.
//

#ifndef PEDAROGUE_ATTACKSYSTEM_HPP
#define PEDAROGUE_ATTACKSYSTEM_HPP


#include <core/ECSTypes.hpp>


class AttackSystem : public System
{
public:
    void attack(Entity attacker, Entity defender);

};


#endif //PEDAROGUE_ATTACKSYSTEM_HPP
