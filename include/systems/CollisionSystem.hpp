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
    /**
     * @brief               Check if the entity has a collision with another entity and create an event for each.
     * @param entity        The entity to check
     * @return              The boolean : "The entity has a collision with something"
     */
    bool check(Entity entity);

};


#endif //PEDAROGUE_COLLISIONSYSTEM_HPP
