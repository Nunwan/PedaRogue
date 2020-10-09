//
// Created by nunwan on 09/10/2020.
//

#include "systems/DropSystem.hpp"
#include "Engine.hpp"


void DropSystem::update()
{
    auto it = mEntities.begin();
    while (it != mEntities.end()) {
        auto entity = *it;
        auto& container = mEngine->GetComponent<Container>(entity);
        auto& toDrop = mEngine->GetComponent<DropItem>(entity);
        if (toDrop.numberToDrop != 0 && container.contains.count(toDrop.objectToDrop)) {
            Event inventoryChanged = {InventoryChanged, 0, 0};
            mEngine->push_Event(inventoryChanged);
            for (int i = 0; i < toDrop.numberToDrop; ++i) {
                mEngine->DestroyEntity(container.contains[toDrop.objectToDrop].back());
                container.contains[toDrop.objectToDrop].pop_back();
                if (container.contains[toDrop.objectToDrop].empty()) {
                    container.contains.erase(toDrop.objectToDrop);
                }
            }
        }
        it++;
        mEngine->DelComponent<DropItem>(entity);
    }
}
