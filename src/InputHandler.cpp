//
// Created by nunwan on 15/06/2020.
//

#include "InputHandler.hpp"
#include "Engine.hpp"


int InputHandler::process_key(EventWin event)
{
    if (mCurrentState == DEFAULT_STATE &&  event.key == TK_ESCAPE) {
        return 1;
    }
    if (mBindings[event.key] == UICommand) {
        mCurrentState = UI_STATE;
    }
    if (mCurrentState == UI_STATE) {
        if (mEngine->mUI.process_key(event)) {
            mCurrentState = DEFAULT_STATE;
        }
    } else {
        mPlayerMovement->update(mBindings[event.key]);
    }
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
    mBindings.insert({TK_I, UICommand});

}
