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
    if (mUIKeys.count(event.key)) {
        mCurrentState = UI_STATE;
    }
    if (mCurrentState == UI_STATE) {
        if (process_key_ui(event)) {
            mCurrentState = DEFAULT_STATE;
        }
    } else {
        if (mBindings.count(event.key)) {
            mEngine->pushCommand(mBindings[event.key]);
        }
    }
    return 0;

}


bool InputHandler::process_key_ui(EventWin event)
{
    if (event.key == TK_ESCAPE) {
        mEngine->mUI.clear_last();
        return true;
    }
    if (mUIBindings.count(event.key)) {
        mEngine->pushCommand(mUIBindings[event.key]);
    }


    return false;
}


InputHandler::InputHandler()
{
    // Bind Default key
    mCurrentState = DEFAULT_STATE;

    mUIKeys.insert(TK_I);

    mUIBindings.insert({TK_I, new OpenInventoryCommand()});
    mUIBindings.insert({TK_DOWN, new UISelectUpCommand});
    mUIBindings.insert({TK_UP, new UISelectDownCommand});


}


void InputHandler::Init()
{
    mBindings.insert({TK_UP, new MovePlayer(mEngine->GetPlayer(), UpPlayer)});
    mBindings.insert({TK_DOWN, new MovePlayer(mEngine->GetPlayer(), DownPlayer)});
    mBindings.insert({TK_RIGHT, new MovePlayer(mEngine->GetPlayer(), RightPlayer)});
    mBindings.insert({TK_LEFT, new MovePlayer(mEngine->GetPlayer(), LeftPlayer)});
    mBindings.insert({TK_F, new MovePlayer(mEngine->GetPlayer(), NextLevelPlayer)});
    mBindings.insert({TK_G, new MovePlayer(mEngine->GetPlayer(), PreviousLevelPlayer)});

}


InputHandler::~InputHandler()
{
    for (auto pair : mBindings) {
        delete pair.second;
    }
}

