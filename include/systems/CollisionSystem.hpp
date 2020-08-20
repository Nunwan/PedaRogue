//
// Created by nunwan on 23/06/2020.
//

#ifndef PEDAROGUE_COLLISIONSYSTEM_HPP
#define PEDAROGUE_COLLISIONSYSTEM_HPP


#include <core/ECSTypes.hpp>


class CollisionSystem : public System
{
public:
    // void update() override;
    bool check(Entity entity);

};


#endif //PEDAROGUE_COLLISIONSYSTEM_HPP
