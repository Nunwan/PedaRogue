//
// Created by nunwan on 14/06/2020.
//
#include "systems/RenderSystem.hpp"
#include "Engine.hpp"


void RenderSystem::render()
{
    for (auto const &entity : mEntities) {
        Render entityRender = mEngine->GetComponent<Render>(entity);
        if (entityRender.to_display) {
            Transform entityPos = mEngine->GetComponent<Transform>(entity);
            mEngine->getMWindow()->print(entityPos.x, entityPos.y, entityRender.glyph, entityRender.color);
        }
    }
}
