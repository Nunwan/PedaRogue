//
// Created by nunwan on 24/06/2020.
//

#include "systems/FoVCompute.hpp"
#include "Engine.hpp"


void FoVCompute::compute()
{
    for (auto const& player : mEntities) {
        auto& playerPos = mEngine->GetComponent<Transform>(player);
        auto level = mEngine->GetLevel(playerPos.levelMap);
        auto& playerStat = mEngine->GetComponent<Stats>(player);
        level->ComputeFOV(playerPos.x, playerPos.y, playerStat.visibility);
    }
}

