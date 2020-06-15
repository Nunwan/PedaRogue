//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_COMPONENTS_HPP
#define PEDAROGUE_COMPONENTS_HPP
#include "Window.hpp"

struct Render {
    char *glyph;
};

struct Transform {
    int x;
    int y;
    int levelMap;
};

struct Map {};
struct Others {};

struct Playable{
    int id;
};

#endif //PEDAROGUE_COMPONENTS_HPP
