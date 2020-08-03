//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_RENDERSYSTEM_HPP
#define PEDAROGUE_RENDERSYSTEM_HPP
#include "core/ECSTypes.hpp"
#include "Components.hpp"
#include "Window.hpp"

#define DIVIDE_SCREEN 4
#define OFFSET_SCREEN 3

#define DEBUG_MAP 1

class RenderSystem : public System
{
public:
    void render();
};

class RenderMapSystem : public RenderSystem
{};

class RenderOthersSystem : public RenderSystem
{};


#endif //PEDAROGUE_RENDERSYSTEM_HPP
