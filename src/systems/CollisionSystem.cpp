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
                if (!entityRigid.can_pass && !entity2Rigid.can_pass) {
                    Event collision = {CollisionEvent, entity, entity2};
                    mEngine->push_Event(collision);
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
        if (mEngine->HasComponent<Transform>(other) && mEngine->HasComponent<RigidBody>(other)) {
            auto &otherPos = mEngine->GetComponent<Transform>(other);
            auto &otherRigid = mEngine->GetComponent<RigidBody>(other);
            if (other != entity && otherPos == entityPos) {
                if (!entityRigid.can_pass && !otherRigid.can_pass) {
                    Event collision = {CollisionEvent, entity, other};
                    mEngine->push_Event(collision);
                    return true;
                }
            }
        }
    }
    return false;
}
