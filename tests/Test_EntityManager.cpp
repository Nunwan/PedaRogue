//
// Created by nunwan on 09/06/2020.
//
#include "EntityManager.hpp"
#include "gtest/gtest.h"


TEST(EntityManagerSuite, CreateEntity)
{
    EntityManager* entityManager = new EntityManager;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(entityManager->CreateEntity(), i);
    }
    delete entityManager;
}


TEST(EntityManagerSuite, DestroyEntity)
{
    auto entityManager = new EntityManager;
    Entity entity = entityManager->CreateEntity();
    entityManager->DestroyEntity(entity);
    EXPECT_EQ(entityManager->CreateEntity(), 0);
    EXPECT_EQ(entityManager->CreateEntity(), 1);
    delete entityManager;
}


TEST(EntityManagerSuit, Signature)
{
    auto entityManager = new EntityManager;
    Entity entity = entityManager->CreateEntity();
    Signature sig;
    sig[3] = true;
    entityManager->SetSignature(entity, sig);
    Signature sigFromEntity = entityManager->getSignature(entity);
    EXPECT_EQ(sig, sigFromEntity);
}
