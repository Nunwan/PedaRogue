//
// Created by nunwan on 28/07/2020.
//

#include "ProcessEvents.hpp"


void process_event(Engine *engine)
{
    while (engine->check_event()) {
        auto event = engine->pop_event();
        switch (event.eventtype) {
            case CollisionEvent: {
                engine->mInputHandler->go_back(event.entity1);
                engine->mInputHandler->go_back(event.entity2);
                Entity player, other;
                if (living_interaction(engine, event.entity1, event.entity2, player, other)) {
                    auto attackEntity = engine->CreateEntity();
                    AttackAttempt attack = {player, other};
                    engine->AddComponent(attackEntity, attack);
                } else if (object_interaction(engine, event.entity1, event.entity2, player, other)) {
                    auto pickEntity = engine->CreateEntity();
                    PickAttempt pick = {player, other};
                    engine->AddComponent(pickEntity, pick);
                }
                break;
            }
            case NextLevelEvent: {
                auto &playerPos = engine->GetComponent<Transform>(event.entity1);
                auto &entity_under_player = engine->getEntityat(playerPos.x, playerPos.y, playerPos.levelMap);
                if (engine->HasComponent<Stairway>(entity_under_player)) {
                    auto& stairway = engine->GetComponent<Stairway>(entity_under_player);
                    if (stairway.direction == DOWN) {
                        return;
                    }
                    engine->level_disable(engine->GetLevel(playerPos.levelMap));
                    playerPos.levelMap++;
                    int levelbefore = playerPos.levelMap;
                    if (levelbefore >= engine->mNbLvl) {
                        engine->create_level();
                        auto &newPos = engine->GetLevel(levelbefore)->getBeginMap();
                        auto &playerPos2 = engine->GetComponent<Transform>(event.entity1);
                        playerPos2.x = newPos.x;
                        playerPos2.y = newPos.y;
                        playerPos2.levelMap = levelbefore;
                    } else {
                        auto nextLevel = engine->GetLevel(playerPos.levelMap);
                        auto stairwayDownPrevious = nextLevel->getMStairwayDown();
                        if (engine->HasComponent<Transform>(stairwayDownPrevious)) {
                            auto& stairwayPos = engine->GetComponent<Transform>(stairwayDownPrevious);
                            playerPos.x = stairwayPos.x;
                            playerPos.y = stairwayPos.y;
                            engine->level_enable(nextLevel);
                        }
                    }
                }
                break;
            }
            case PreviousLevelEvent: {
                auto &playerPos = engine->GetComponent<Transform>(event.entity1);
                auto &entity_under_player = engine->getEntityat(playerPos.x, playerPos.y, playerPos.levelMap);
                if (engine->HasComponent<Stairway>(entity_under_player)) {
                    auto& stairway = engine->GetComponent<Stairway>(entity_under_player);
                    if (stairway.direction == UP) {
                        return;
                    }
                    engine->level_disable(engine->GetLevel(playerPos.levelMap));
                    playerPos.levelMap--;
                    auto previousLevel = engine->GetLevel(playerPos.levelMap);
                    auto stairwayUpPrevious = previousLevel->getMStairwayUp();
                    if (engine->HasComponent<Transform>(stairwayUpPrevious)) {
                        auto& stairwayPos = engine->GetComponent<Transform>(stairwayUpPrevious);
                        playerPos.x = stairwayPos.x;
                        playerPos.y = stairwayPos.y;
                        engine->level_enable(previousLevel);
                    }
                }
            }
        }
    }
}


bool living_interaction(Engine* engine, Entity entity1, Entity entity2, Entity &player, Entity &other)
{
   if (engine->HasComponent<Playable>(entity1) && engine->HasComponent<Living>(entity2)) {
       player = entity1;
       other = entity2;
       return true;
   }
   if (engine->HasComponent<Playable>(entity2) && engine->HasComponent<Living>(entity1)) {
       player = entity2;
       other = entity1;
       return true;
   }
    return false;
}

bool object_interaction(Engine* engine, Entity entity1, Entity entity2, Entity &player, Entity &other)
{
    if (engine->HasComponent<Playable>(entity1) && engine->HasComponent<Object>(entity2)) {
        player = entity1;
        other = entity2;
        return true;
    }
    if (engine->HasComponent<Playable>(entity2) && engine->HasComponent<Object>(entity1)) {
        player = entity2;
        other = entity1;
        return true;
    }
    return false;
}
