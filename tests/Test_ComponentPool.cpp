//
// Created by nunwan on 09/06/2020.
//

#include <vector>
#include "gtest/gtest.h"
#include "ComponentPool.hpp"
#include "EntityManager.hpp"


struct Position {
    int x;
    int y;
};

TEST(ComponentPoolSuite, Link)
{
    ComponentPool<Position> ComponentPoolPos;
    EntityManager entityManager;
    Entity entity = entityManager.CreateEntity();
    struct Position posEntity = {2, 4};
    ComponentPoolPos.link(entity, posEntity);
    EXPECT_EQ(posEntity.x, ComponentPoolPos.Get(entity).x);
    EXPECT_EQ(posEntity.y, ComponentPoolPos.Get(entity).y);
    EXPECT_TRUE(ComponentPoolPos.exist(entity));
}


TEST(ComponentPoolSuite, Unlink)
{
    ComponentPool<Position> ComponentPoolPos;
    EntityManager entityManager;
    Entity entity = entityManager.CreateEntity();
    struct Position posEntity = {2, 4};
    ComponentPoolPos.link(entity, posEntity);
    ComponentPoolPos.unlink(entity);
    EXPECT_FALSE(ComponentPoolPos.exist(entity));
}


TEST(ComponentPoolSuite, Get)
{

    ComponentPool<Position> ComponentPoolPos;
    EntityManager entityManager;
    Entity entity = entityManager.CreateEntity();
    Entity entity2 = entityManager.CreateEntity();
    struct Position posEntity = {2, 4};
    struct Position posEntity2 = {3, 4};
    ComponentPoolPos.link(entity, posEntity);
    ComponentPoolPos.link(entity2, posEntity2);
    EXPECT_EQ(posEntity.x, ComponentPoolPos.Get(entity).x);
    EXPECT_EQ(posEntity2.x, ComponentPoolPos.Get(entity2).x);
}


TEST(ComponentPoolSuite, Iterator)
{
    ComponentPool<Position> ComponentPoolPos;
    EntityManager entityManager;
    struct Position posEntity = {1, 1};
    for (int i = 0; i < 20; ++i) {
        Entity entity = entityManager.CreateEntity();
        posEntity.x = i;
        ComponentPoolPos.link(entity, posEntity);
    }
    std::vector<Position>::iterator it = ComponentPoolPos.iterBeginComp();
    int i = 0;
    for (it; it != ComponentPoolPos.iterEndComp(); ++it) {
        EXPECT_EQ(it->x, i);
        i++;
    }
    EXPECT_EQ(i, 20);
}
