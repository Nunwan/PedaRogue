//
// Created by nunwan on 08/06/2020.
//

#ifndef PEDAROGUE_ENTITYMANAGER_HPP
#define PEDAROGUE_ENTITYMANAGER_HPP


#include <unordered_map>
#include <queue>
#include <cassert>
#include "core/EntityManager.hpp"
#include "ECSTypes.hpp"


/**
 * @brief   Class used to manage entities
 */
class EntityManager {
private:
    int mIdMax;
    // Entities which were destroyed but can be used
    std::queue<Entity> mAvailableEntities;
    std::unordered_map<Entity, Signature> mSignatures;

public:
    EntityManager();
    /**
     * @brief       Create an entity and return the id
     * @return      Free ID to be used
     */
    Entity CreateEntity();
    /**
     * @brief           Destroy entity, reset the signature and make it available
     * @param entity    Entity to destroy. Assume the entity exists. If not the behavior is undefined
     */
    void DestroyEntity(Entity entity);
    /**
     * @brief               Link a signature to an entity
     * @param entity        Entity to link with a signature. Assume the entity exists. If not, the behavior is undefined
     * @param signature     Existing signature to link
     */
    void SetSignature(Entity entity, Signature signature);

    /**
     * @brief               Return the Signature linked to the entity
     * @param entity        The entity which the signature is wanted. Assume it exists. If not, the behavior is undefined
     * @return              The signature linked to the given entity
     */
    Signature getSignature(Entity entity);
};


EntityManager::EntityManager()
{
    mIdMax = 0;
}


Entity EntityManager::CreateEntity()
{
    if (!mAvailableEntities.empty())
    {
        Entity entity = mAvailableEntities.front();
        mAvailableEntities.pop();
        return entity;
    }
    Entity entity = mIdMax;
    mIdMax++;
    return entity;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
    assert(entity < mIdMax);
    mSignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    assert(entity < mIdMax);
    return mSignatures[entity];
}

void EntityManager::DestroyEntity(Entity entity)
{
    assert(entity < mIdMax);
    mSignatures[entity].reset();
    mAvailableEntities.push(entity);
}

#endif //PEDAROGUE_ENTITYMANAGER_HPP
