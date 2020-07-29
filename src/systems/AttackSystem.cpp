//
// Created by nunwan on 28/07/2020.
//

#include <iostream>
#include "systems/AttackSystem.hpp"
#include "Engine.hpp"


void AttackSystem::update()
{
    bool b = false;
    for (auto it = mEntities.begin(); it != mEntities.end(); ++it) {
        auto entity = *it;
        auto& attack = mEngine->GetComponent<AttackAttempt>(entity);
        auto& attacker = attack.attacker;
        auto& target = attack.target;
        //TODO
        for (auto& entity : mEntities) {
            std::cout << entity << std::endl;
        }
        std::cout << "fin" << std::endl;
        mEngine->DelComponent<AttackAttempt>(entity);
        for (auto& entity : mEntities) {
            std::cout << entity << std::endl;
        }
        std::cout << "fin" << std::endl;
        if (mEngine->HasComponent<Living>(target)) {
            mEngine->DestroyEntity(target);
            b = true;
            break;
        }
        for (auto& entity : mEntities) {
            std::cout << entity << std::endl;
        }
        std::cout << "fin" << std::endl;
    }
    if (b) {
        update();
    }
}
