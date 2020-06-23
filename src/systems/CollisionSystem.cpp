//
// Created by nunwan on 23/06/2020.
//

#include "systems/CollisionSystem.hpp"
#include "Engine.hpp"


void CollisionSystem::update()
{
    for (auto& entity : mEntities) {
        auto& entityPos = mEngine->GetComponent<Transform>(entity);
        auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
        for (auto& entity2 : mEntities) {
            auto& entity2Pos = mEngine->GetComponent<Transform>(entity2);
            auto& entity2Rigid = mEngine->GetComponent<RigidBody>(entity2);
            if (entity != entity2 && entity2Pos == entityPos) {
               if (mEngine->HasComponent<Moveable>(entity)) {
                   auto& entityMove = mEngine->GetComponent<Moveable>(entity);
                   if (entityMove.direction % 2) {
                       int negative = entityMove.direction == 1?1:-1;
                       entityPos.y -= negative;
                   } else {
                       int negative = entityMove.direction == 0?1:-1;
                       entityPos.x -= negative;
                   }
               }
                if (mEngine->HasComponent<Moveable>(entity2)) {
                    auto& entity2Move = mEngine->GetComponent<Moveable>(entity2);
                    if (entity2Move.direction % 2) {
                        int negative = entity2Move.direction == 1?1:-1;
                        entity2Pos.y -= negative;
                    } else {
                        int negative = entity2Move.direction == 0?1:-1;
                        entity2Pos.x -= negative;
                    }
                }
            }
        }
    }

}


bool CollisionSystem::check(Entity entity)
{
    auto& entityPos = mEngine->GetComponent<Transform>(entity);
    auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
    for (auto& other : mEntities) {
        auto& otherPos = mEngine->GetComponent<Transform>(other);
        auto& otherRigid = mEngine->GetComponent<RigidBody>(other);
        if (other != entity && otherPos == entityPos && !otherRigid.can_pass) {
            return true;
        }
    }
    return false;

}
