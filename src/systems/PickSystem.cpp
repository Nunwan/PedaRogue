//
// Created by nunwan on 30/07/2020.
//

#include "systems/PickSystem.hpp"
#include "Engine.hpp"


void PickSystem::update()
{
    bool b = false;
    for (auto const& entity : mEntities) {
        auto& pickattempt = mEngine->GetComponent<PickAttempt>(entity);
        auto& player = pickattempt.player;
        auto& object = pickattempt.object;
        mEngine->DelComponent<Transform>(object);
        mEngine->DelComponent<Render>(object);
        auto& containerPlayer = mEngine->GetComponent<Container>(player);
        auto& nameObject = mEngine->GetComponent<Namable>(object);
        if (!containerPlayer.contains.count(nameObject.name)) {
            containerPlayer.contains[nameObject.name].push_back(object);
        }
        else {
            std::vector<Entity> objvector;
            objvector.push_back(object);
            containerPlayer.contains.insert({nameObject.name, objvector});
        }
        mEngine->DelComponent<PickAttempt>(entity);
        b = true;
        break;
    }
    if (b) {
        update();
    }

}
