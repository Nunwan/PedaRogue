//
// Created by nunwan on 28/07/2020.
//

#include <iostream>
#include "systems/AttackSystem.hpp"
#include "Engine.hpp"


void AttackSystem::update()
{
    auto it = mEntities.begin();
    while (it != mEntities.end()) {
        auto entity = *it;
        auto& attack = mEngine->GetComponent<AttackAttempt>(entity);
        auto& attacker = attack.attacker;
        auto& target = attack.target;
        if (mEngine->HasComponent<Living>(target)) {
            // FOR TEST
            if (mEngine->HasComponent<Namable>(target)) {
                auto& targetName = mEngine->GetComponent<Namable>(target);
                Message attackMessage = {"You're attacking a " + targetName.name + ".", 0xff, 0xff, 0xff};
                mEngine->mUI.push_message(attackMessage);
            }
            mEngine->DestroyEntity(target);
            // FOR TEST
            if (mEngine->HasComponent<Namable>(target)) {
                auto& targetName = mEngine->GetComponent<Namable>(target);
                Message dieMessage = {"You killed the " + targetName.name + ".", 0xff, 0xff, 0xff};
                mEngine->mUI.push_message(dieMessage);
            }
        }
        if (mEngine->HasComponent<Stats>(attacker)) {
            auto& attackerStat = mEngine->GetComponent<Stats>(attacker);
            attackerStat.stats["pv"] -= 1;
            // FOR TEST
            Message damageMessage = {"You lost 1 PV", 0xff, 0xff, 0xff};
            mEngine->mUI.push_message(damageMessage);
        }
        it++;
        mEngine->DelComponent<AttackAttempt>(entity);
        mEngine->DestroyEntity(entity);
    }
}
