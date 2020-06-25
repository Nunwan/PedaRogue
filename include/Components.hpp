//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_COMPONENTS_HPP
#define PEDAROGUE_COMPONENTS_HPP
#include "Window.hpp"

struct Render {
    char *glyph;
    color_t color;
    bool to_display;
};

struct Transform {
    int x;
    int y;
    int levelMap;
    bool operator==(Transform t1) const
    {
        return t1.x == this->x && t1.y == this->y && t1.levelMap == this->levelMap;
    }
};

struct RigidBody {
    bool can_pass;
    bool transparent;
};

struct Map {};
struct NotMap {};

struct Playable{
    int id;
};

struct Moveable {
    int direction;
};

struct Stats {
    int visibility;
};

struct Light {};
#endif //PEDAROGUE_COMPONENTS_HPP
