//
// Created by nunwan on 15/06/2020.
//

#include "InputHandler.hpp"


int InputHandler::process_key(Event event)
{
    if (event.key == TK_ESCAPE) {
        return 1;
    }
    mPlayerMovement->update(mBindings[event.key]);
    return 0;

}


void InputHandler::Init()
{
    mPlayerMovement = mECSManager->RegisterSystem<PlayerMovement>();
    mECSManager->UseComponent<PlayerMovement, Playable>();
    mECSManager->UseComponent<PlayerMovement, Transform>();
    mECSManager->UseComponent<PlayerMovement, Others>();
    mECSManager->UseComponent<PlayerMovement, Render>();

    // Bind Default key
    mBindings.insert({TK_UP, UpPlayer});
    mBindings.insert({TK_DOWN, DownPlayer});
    mBindings.insert({TK_RIGHT, RightPlayer});
    mBindings.insert({TK_LEFT, LeftPlayer});
}


