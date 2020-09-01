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

#define DEBUG_MAP 0

class RenderSystem : public System
{
public:
    /**
     * Loop through all the render entity and display them if it has to be
     */
    void render() override;
};

class RenderMapSystem : public RenderSystem
{};

class RenderOthersSystem : public RenderSystem
{};


#endif //PEDAROGUE_RENDERSYSTEM_HPP
