//
// Created by nunwan on 28/07/2020.
//

#ifndef PEDAROGUE_PROCESSEVENTS_HPP
#define PEDAROGUE_PROCESSEVENTS_HPP
#include "Engine.hpp"

void process_event(Engine* engine);

bool living_interaction(Engine* engine, Entity entity1, Entity entity2, Entity& player, Entity& other);

#endif //PEDAROGUE_PROCESSEVENTS_HPP
