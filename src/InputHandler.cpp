//
// Created by nunwan on 15/06/2020.
//

#include "InputHandler.hpp"
#include "Engine.hpp"


int InputHandler::process_key(EventWin event)
{
    if (event.key == TK_ESCAPE) {
        return 1;
    }
    mPlayerMovement->update(mBindings[event.key]);
    return 0;

}


void InputHandler::Init()
{
    mPlayerMovement = mEngine->RegisterSystem<PlayerMovement>(mEngine);
    mEngine->UseComponent<PlayerMovement, Playable>();
    mEngine->UseComponent<PlayerMovement, Transform>();
    mEngine->UseComponent<PlayerMovement, NotMap>();
    mEngine->UseComponent<PlayerMovement, Render>();
    mEngine->UseComponent<PlayerMovement, Moveable>();

    // Bind Default key
    mBindings.insert({TK_UP, UpPlayer});
    mBindings.insert({TK_DOWN, DownPlayer});
    mBindings.insert({TK_RIGHT, RightPlayer});
    mBindings.insert({TK_LEFT, LeftPlayer});
    mBindings.insert({TK_F, NextLevelPlayer});
    mBindings.insert({TK_G, PreviousLevelPlayer});
}


void InputHandler::go_back(Entity entity)
{
    mPlayerMovement->go_back(entity);
}


