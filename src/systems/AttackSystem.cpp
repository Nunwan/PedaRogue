//
// Created by nunwan on 28/07/2020.
//

#include <iostream>
#include "systems/AttackSystem.hpp"
#include "Engine.hpp"


void AttackSystem::update()
{
    bool b = false;
    // TODO Change this barbaric version
    for (auto it = mEntities.begin(); it != mEntities.end(); ++it) {
        auto entity = *it;
        auto& attack = mEngine->GetComponent<AttackAttempt>(entity);
        auto& attacker = attack.attacker;
        auto& target = attack.target;
        mEngine->DelComponent<AttackAttempt>(entity);
        if (mEngine->HasComponent<Living>(target)) {
            mEngine->DestroyEntity(target);
            b = true;
            break;
        }
    }
    if (b) {
        update();
    }
}
