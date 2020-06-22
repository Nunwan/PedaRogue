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
        std::cout << posEntity.x << posEntity.y << std::endl;
    }
}
