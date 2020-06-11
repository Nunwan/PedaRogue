//
// Created by nunwan on 11/06/2020.
//

#include "gtest/gtest.h"
#include "core/ECSManager.hpp"
#include "core/ECSTypes.hpp"

class System_zero : public System {
public:
    int Update()
    {
        for (auto const& entity : mEntities){
            if (entity == 1)
            {
                return 1;
            }
        }
        return 0;
    }
};

struct Position {
    int x;
    int y;
};

struct Life {
    int pv;
};

TEST(ECSManager_Suite, Use)
{
    ECSManager ecsManager;
    Entity entity0 = ecsManager.CreateEntity();
    Entity entity1 = ecsManager.CreateEntity();

    ecsManager.RegisterComponent<Position>();
    ecsManager.RegisterComponent<Life>();

    auto system_zero = ecsManager.RegisterSystem<System_zero>();
    ecsManager.UseComponent<System_zero, Life>();
    Position pos = {2, 3};
    Life life = {10};

    EXPECT_EQ(system_zero->Update(), 0);
    ecsManager.AddComponent(entity0, pos);
    EXPECT_EQ(system_zero->Update(), 0);
    ecsManager.AddComponent(entity1, life);
    EXPECT_EQ(system_zero->Update(), 1);



}

