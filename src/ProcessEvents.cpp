//
// Created by nunwan on 28/07/2020.
//

#include "ProcessEvents.hpp"


void process_event(Engine *engine)
{
    while (engine->check_event()) {
        auto event = engine->pop_event();
        switch (event.eventtype) {
            case CollisionEvent:
                engine->mInputHandler->go_back(event.entity1);
                engine->mInputHandler->go_back(event.entity2);
                Entity player, other;
                if (living_interaction(engine, event.entity1, event.entity2, player, other)) {
                    AttackAttempt attack = {other};
                    engine->AddComponent(player, attack);

                }
                break;
            default:
                break;
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
