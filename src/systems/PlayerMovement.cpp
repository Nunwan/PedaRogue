//
// Created by nunwan on 15/06/2020.
//

#include "PlayerMovement.hpp"


void PlayerMovement::update(CommandType commandType)
{
    for (auto const& entity : mEntities) {
        Transform& posEntity = mECSManager->GetComponent<Transform>(entity);
        if (commandType == UpPlayer) {
            posEntity.y--;
        }
        else if (commandType == DownPlayer) {
            posEntity.y = posEntity.y + 1;
        }
        else if (commandType == RightPlayer) {
            posEntity.x++;
        }
        else if (commandType == LeftPlayer) {
            posEntity.x--;
        }
    }
}
