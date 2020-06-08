//
// Created by nunwan on 08/06/2020.
//

#ifndef PEDAROGUE_ENTITYMANAGER_HPP
#define PEDAROGUE_ENTITYMANAGER_HPP


#include <unordered_map>
#include <queue>
#include "ECSTypes.hpp"

class EntityManager {
private:
    int mIDmax;
    // Entities which were destroyed but can be used
    std::queue<Entity> mAvailableEntities;
    std::unordered_map<Entity, Signature> mSignatures;

public:
    EntityManager();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void SetSignature(Entity entity, Signature signature);

    Signature getSignature(Entity entity);

};


#endif //PEDAROGUE_ENTITYMANAGER_HPP
