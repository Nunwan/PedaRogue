//
// Created by nunwan on 08/06/2020.
//

#include <cassert>
#include "EntityManager.hpp"

EntityManager::EntityManager()
{
    mIDmax = 0;
}

Entity EntityManager::CreateEntity()
{
    if (!mAvailableEntities.empty())
    {
        Entity entity = mAvailableEntities.front();
        mAvailableEntities.pop();
        return entity;
    }
    Entity entity = mIDmax;
    mIDmax++;
    return entity;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
    assert(entity < mIDmax);
    mSignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    assert(entity < mIDmax);
    return mSignatures[entity];
}

void EntityManager::DestroyEntity(Entity entity)
{
    assert(entity < mIDmax);
    mSignatures[entity].reset();
    mAvailableEntities.push(entity);
}
