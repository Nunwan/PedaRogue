//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_COMPONENTS_HPP
#define PEDAROGUE_COMPONENTS_HPP
#include <unordered_map>
#include "Window.hpp"
#include "core/ECSTypes.hpp"

#define UP 0
#define DOWN 1
/**
 * @brief  Render component for display on screen
 *
 *          glyph       Symbol representing the Entity
 *          color       Color to apply to the glyph
 *          to_display  boolean to know if the entity has to be displayed
 */
struct Render {
    char *glyph;
    color_t color;
    bool to_display;
};

/**
 * @brief   Transform component to the position in the world
 *          x,y             2D Coordinates of the entity
 *          levelMap        The level of the map in the entity is
 */
struct Transform {
    int x;
    int y;
    int levelMap;
    bool operator==(Transform t1) const
    {
        return t1.x == this->x && t1.y == this->y && t1.levelMap == this->levelMap;
    }
};

/**
 * @brief   RigidBody component for collision and transparency.
 *          can_pass    represent if the entity is rigid
 *          transparent give the possibility to see through the entity
 */
struct RigidBody {
    bool can_pass;
    bool transparent;
};

/**
 * @brief   Map component to indicate to RenderSystem that the entity is an Map object to display
 */
struct Map {};

/**
 * @brief   Map component to indicate to RenderSystem that the entity is an NotMap (object, monsters) object to display
 */
struct NotMap {};

/**
 * @brief   Component representing the possibility to play this entity
 *          id      Id in the vector of players.
 */
struct Playable{
    int id;
};

/**
 * @brief   Component to indicate if the entity can be moved
 *          direction   Represent the vector of direction between RIGHT, LEFT, UP, DOWN
 */
struct Moveable {
    int direction;
};

/**
 * @brief   Stats for players : Differents values for different ability
 *          visibility      Range of the vision circle of the entity
 */
struct Stats {
    std::unordered_map<std::string, int> stats;
    Stats()
    {
        stats.insert({"visibility", 0});
        stats.insert({"pv", 0});
        stats.insert({"mana", 0});

    }
};

/**
 * @brief   Component which indicates that the entity is a lighting source.
 */
struct Light {};

struct Living {};

struct Object {};

// Direction : UP = 0 Down = 1
struct Stairway {
    int direction;
};

struct AttackAttempt {
    Entity attacker;
    Entity target;
};

struct PickAttempt {
    Entity player;
    Entity object;
};

struct BackAttempt {
    Entity to_move;
};

struct Container {
    std::unordered_map<std::string, std::vector<Entity>> contains;
};

struct Namable {
    std::string name;
};

#endif //PEDAROGUE_COMPONENTS_HPP
