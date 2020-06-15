//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_COMPONENTS_HPP
#define PEDAROGUE_COMPONENTS_HPP
#include "Window.hpp"

struct Render {
    int glyph;
    TCODColor  color;
};

struct Transform {
    int x;
    int y;
    int levelMap;
};

struct Map {};
struct Others {};

#endif //PEDAROGUE_COMPONENTS_HPP
