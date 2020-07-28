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
                break;
            default:
                break;
        }
    }
}
