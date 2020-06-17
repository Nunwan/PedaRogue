//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_COMPONENTS_HPP
#define PEDAROGUE_COMPONENTS_HPP
#include "Window.hpp"

struct Render {
    char *glyph;
    color_t color;
};

struct Transform {
    int x;
    int y;
    int levelMap;
};

struct RigidBody {
    bool transparent;
};

struct Map {};
struct NotMap {};

struct Playable{
    int id;
};

#endif //PEDAROGUE_COMPONENTS_HPP
