//
// Created by nunwan on 10/06/2020.
//
#include "gtest/gtest.h"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"

struct Position {
    int x;
    int y;
};

struct Life {
    int PV;
};

TEST(ComponentManagerSuite, EntityDestroyed)
{
    EntityManager entityManager;
    ComponentManager componentManager;
    componentManager.RegisterComponent<Position>();
    componentManager.RegisterComponent<Life>();
    Entity entity1 = entityManager.CreateEntity();
    Entity entity2 = entityManager.CreateEntity();
    Entity entity3 = entityManager.CreateEntity();
    Position pos1 = {2, 3};
    Position pos2 = {3,4};
    Position pos3 = {4, 5};
    Life life1 = {20};
    Life life2 = {30};
    Life life3 = {40};
    componentManager.AddComponent(entity1, pos1);
    componentManager.AddComponent(entity1, life1);
    componentManager.AddComponent(entity2, pos2);
    componentManager.AddComponent(entity2, life2);
    componentManager.AddComponent(entity3, pos3);
    componentManager.AddComponent(entity3, life3);
    Position &pos1expected = componentManager.GetComponent<Position>(entity1);
    EXPECT_EQ(pos1expected.x, pos1.x);
    componentManager.EntityDestroyed(entity1);
    entityManager.DestroyEntity(entity1);
    EXPECT_EQ(componentManager.GetComponentPool<Position>()->getSparse().count(entity1), 0);
    EXPECT_EQ(componentManager.GetComponentPool<Life>()->getSparse().count(entity1), 0);
}


TEST(ComponentManagerSuite, DelComponent)
{
    EntityManager entityManager;
    ComponentManager componentManager;
    componentManager.RegisterComponent<Position>();
    componentManager.RegisterComponent<Life>();
    Entity entity1 = entityManager.CreateEntity();
    Entity entity2 = entityManager.CreateEntity();
    Entity entity3 = entityManager.CreateEntity();
    Position pos1 = {2, 3};
    Position pos2 = {3,4};
    Position pos3 = {4, 5};
    Life life1 = {20};
    Life life2 = {30};
    Life life3 = {40};
    componentManager.AddComponent(entity1, pos1);
    componentManager.AddComponent(entity1, life1);
    componentManager.AddComponent(entity2, pos2);
    componentManager.AddComponent(entity2, life2);
    componentManager.AddComponent(entity3, pos3);
    componentManager.AddComponent(entity3, life3);
    EXPECT_EQ(componentManager.GetComponentPool<Position>()->getSparse().count(entity1), 1);
    componentManager.DelComponent<Position>(entity1);
    EXPECT_EQ(componentManager.GetComponentPool<Position>()->getSparse().count(entity1), 0);
}

TEST(ComponentManagerSuite, Iterator)
{
    ComponentManager componentManager;
    EntityManager entityManager;
    componentManager.RegisterComponent<Position>();
    struct Position posEntity = {1, 1};
    for (int i = 0; i < 20; ++i) {
        Entity entity = entityManager.CreateEntity();
        posEntity.x = i;
        componentManager.AddComponent(entity, posEntity);
    }
    std::vector<Position>::iterator it = componentManager.beginIterateComp<Position>();
    int i = 0;
    for (it; it != componentManager.endIterateComp<Position>(); ++it) {
        EXPECT_EQ(it->x, i);
        i++;
    }
    EXPECT_EQ(i, 20);
}
