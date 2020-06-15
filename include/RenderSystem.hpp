//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_RENDERSYSTEM_HPP
#define PEDAROGUE_RENDERSYSTEM_HPP
#include "core/ECSTypes.hpp"
#include "core/ECSManager.hpp"
#include "Components.hpp"
#include "Window.hpp"


class RenderSystem : public System
{
public:
    void render(std::shared_ptr<Window> window);
};

class RenderMapSystem : public RenderSystem
{};

class RenderOthersSystem : public RenderSystem
{};


#endif //PEDAROGUE_RENDERSYSTEM_HPP
