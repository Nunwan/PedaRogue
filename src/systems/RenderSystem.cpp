//
// Created by nunwan on 14/06/2020.
//
#include "systems/RenderSystem.hpp"
#include "Engine.hpp"


void RenderSystem::render()
{
    mEngine->getMWindow()->select_win(WIN_JEU);
    auto& player = mEngine->GetPlayer();
    // We know player has a Transform component so it is not necessary to check
    auto& playerPos = mEngine->GetComponent<Transform>(player);
    // Variables for the camera
    int width_screen_game = 2 * WIDTH_SCREEN / 3;
    int height_screen_game = 4 * HEIGHT_SCREEN/5;
    int quotient_divide_x = playerPos.x / (width_screen_game/DIVIDE_SCREEN);
    int quotient_divide_y = playerPos.y / (height_screen_game/DIVIDE_SCREEN);
    bool to_move_x = quotient_divide_x >= OFFSET_SCREEN;
    bool to_move_y = quotient_divide_y >= OFFSET_SCREEN;
    for (auto const &entity : mEntities) {
        Render entityRender = mEngine->GetComponent<Render>(entity);
        Transform entityPos = mEngine->GetComponent<Transform>(entity);
        int x_screen = entityPos.x;
        int y_screen = entityPos.y;
        // camera moving
        if (to_move_x) {
            x_screen -= playerPos.x - (OFFSET_SCREEN*width_screen_game / DIVIDE_SCREEN);
        }
        if (to_move_y) {
            y_screen -= playerPos.y - (OFFSET_SCREEN*height_screen_game / DIVIDE_SCREEN);
        }
#if DEBUG_MAP == 0
        if (entityRender.to_display && x_screen < width_screen_game && y_screen < height_screen_game && x_screen >= 0 && y_screen >= 0) {
#endif
            mEngine->getMWindow()->print(x_screen, y_screen, entityRender.glyph, entityRender.color);
#if DEBUG_MAP == 0
        }
#endif
    }
}

