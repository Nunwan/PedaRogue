//
// Created by nunwan on 08/06/2020.
//

#include <cassert>
#include "EntityManager.hpp"
#include "gtest/gtest.h"


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
