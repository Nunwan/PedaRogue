//
// Created by nunwan on 30/08/2020.
//

#include "systems/BackSystem.hpp"
#include "Engine.hpp"


void BackSystem::update()
{
    auto it = mEntities.begin();
    while (it != mEntities.end()) {
        auto entity = *it;
        auto& backatt = mEngine->GetComponent<BackAttempt>(entity);
        auto to_move = backatt.to_move;
        if (mEngine->HasComponent<Moveable>(to_move)) {
            auto& MoveEntity = mEngine->GetComponent<Moveable>(to_move);
            auto& posEntity = mEngine->GetComponent<Transform>(to_move);
            switch (MoveEntity.direction) {
                case DIR_UP:
                    posEntity.y++;
                    break;
                case DIR_DOWN:
                    posEntity.y--;
                    break;
                case DIR_LEFT:
                    posEntity.x++;
                    break;
                case DIR_RIGHT:
                    posEntity.x--;
                    break;
                default:
                    break;
            }
        }
        it++;
        mEngine->DelComponent<BackAttempt>(entity);
        mEngine->DestroyEntity(entity);
    }
}
