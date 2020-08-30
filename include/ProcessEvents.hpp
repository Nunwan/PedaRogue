//
// Created by nunwan on 28/07/2020.
//

#ifndef PEDAROGUE_PROCESSEVENTS_HPP
#define PEDAROGUE_PROCESSEVENTS_HPP
#include "Engine.hpp"

/**
 * @brief                   Run through the queue of events and process each of them
 * @param engine            Callback pointers to the engine
 */
void process_event(Engine* engine);

/**
 * @brief                   Check if one entity is a living object and the other is the player and put the
 *                          good one in the good reference
 * @param engine            Callback pointers to the engine
 * @param entity1           The first entity to check
 * @param entity2           The second entity to check
 * @param player            The reference to the player variable entity
 * @param other             The reference to the other entity
 * @return                  If one of the entity check is playable and the other is a living entity
 */
bool living_interaction(Engine* engine, Entity entity1, Entity entity2, Entity& player, Entity& other);

/**
 * @brief                   Check if one entity is an object and the other is the player and put the
 *                          good one in the good reference
 * @param engine            Callback pointers to the engine
 * @param entity1           The first entity to check
 * @param entity2           The second entity to check
 * @param player            The reference to the player variable entity
 * @param other             The reference to the other entity
 * @return                  If one of the entity check is playable and the other is a object entity
 */
bool object_interaction(Engine* engine, Entity entity1, Entity entity2, Entity& player, Entity& other);

#endif //PEDAROGUE_PROCESSEVENTS_HPP
