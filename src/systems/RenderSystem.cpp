//
// Created by nunwan on 14/06/2020.
//
#include "RenderSystem.hpp"


void RenderSystem::render(std::shared_ptr<Window> window)
{
    for (auto const &entity : mEntities) {
        Render entityRender = mECSManager->GetComponent<Render>(entity);
        Transform entityPos = mECSManager->GetComponent<Transform>(entity);
        window->print(entityPos.x, entityPos.y, entityRender.glyph, entityRender.color);
    }
}
