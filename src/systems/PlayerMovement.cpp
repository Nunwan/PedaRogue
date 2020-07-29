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
        mEngine->mCollisionSystem->check(entity);

        // std::cout << posEntity.x << posEntity.y << std::endl;
    }
}


void PlayerMovement::go_back(Entity to_move)
{
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

}
