//
// Created by nunwan on 14/06/2020.
//
#include "systems/RenderSystem.hpp"
#include "Engine.hpp"


void RenderSystem::render()
{
    auto& player = mEngine->GetPlayer();
    // We know player has a Transform component so it is not necessary to check
    auto& playerPos = mEngine->GetComponent<Transform>(player);
    // Variables for the camera
    int quotient_divide_x = playerPos.x / (WIDTH_SCREEN/DIVIDE_SCREEN);
    int quotient_divide_y = playerPos.y / (HEIGHT_SCREEN/DIVIDE_SCREEN);
    bool to_move_x = quotient_divide_x >= OFFSET_SCREEN;
    bool to_move_y = quotient_divide_y >= OFFSET_SCREEN;
    for (auto const &entity : mEntities) {
        Render entityRender = mEngine->GetComponent<Render>(entity);
        Transform entityPos = mEngine->GetComponent<Transform>(entity);
        int x_screen = entityPos.x;
        int y_screen = entityPos.y;
        // camera moving
        if (to_move_x) {
            x_screen -= playerPos.x - (OFFSET_SCREEN*WIDTH_SCREEN / DIVIDE_SCREEN);
        }
        if (to_move_y) {
            y_screen -= playerPos.y - (OFFSET_SCREEN*HEIGHT_SCREEN / DIVIDE_SCREEN);
        }
#if DEBUG_MAP == 0
        if (entityRender.to_display) {
#endif
            mEngine->getMWindow()->print(x_screen, y_screen, entityRender.glyph, entityRender.color);
#if DEBUG_MAP == 0
        }
#endif
    }
}

