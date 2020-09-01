//
// Created by nunwan on 15/06/2020.
//

#include <iostream>
#include "systems/PlayerMovement.hpp"
#include "Components.hpp"
#include "Engine.hpp"


void PlayerMovement::update(CommandType commandType)
{
    for (auto const& entity : mEntities) {
        Transform& posEntity = mEngine->GetComponent<Transform>(entity);
        auto& MoveEntity = mEngine->GetComponent<Moveable>(entity);
        if (commandType == UpPlayer) {
            posEntity.y--;
            MoveEntity.direction = DIR_UP;
        }
        else if (commandType == DownPlayer) {
            posEntity.y = posEntity.y + 1;
            MoveEntity.direction = DIR_DOWN;
        }
        else if (commandType == RightPlayer) {
            posEntity.x++;
            MoveEntity.direction = DIR_RIGHT;
        }
        else if (commandType == LeftPlayer) {
            posEntity.x--;
            MoveEntity.direction = DIR_LEFT;
        }
        else if (commandType == NextLevelPlayer) {
            Event uplvl;
            uplvl.eventtype = NextLevelEvent;
            uplvl.entity1 = entity;
            mEngine->push_Event(uplvl);
        }
        else if (commandType == PreviousLevelPlayer) {
            Event downlvl;
            downlvl.eventtype = PreviousLevelEvent;
            downlvl.entity1 = entity;
            mEngine->push_Event(downlvl);
        }
        mEngine->getCollisionSystem()->check(entity);

        // std::cout << posEntity.x << posEntity.y << std::endl;
    }
}
