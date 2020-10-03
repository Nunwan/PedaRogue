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
        mEngine->pushCommand(mBindings[event.key]);
    }
    return 0;

}


bool InputHandler::process_key_ui(EventWin event)
{
    if (event.key == TK_ESCAPE) {
        mEngine->mUI.clear_last();
        return true;
    }
    auto command = mUIBindings[event.key];
   /* switch (command) {
        case OpenInventoryPlayer: {
            mEngine->getMInventoryPlayerSystem()->refresh_list();
            mEngine->getMInventoryPlayerSystem()->display();
            break;
        }
        case UpMenu: {
            mEngine->mUI.getLastBox()->select_previous();
            break;
        }
        case DownMenu: {
            mEngine->mUI.getLastBox()->select_next();
            break;
        }
        default:
            break;
    }*/
    return false;
}


InputHandler::InputHandler()
{
    // Bind Default key
    mCurrentState = DEFAULT_STATE;

    mUIKeys.insert(TK_I);

    /*mUIBindings.insert({TK_I, OpenInventoryPlayer});
    mUIBindings.insert({TK_DOWN, DownMenu});
    mUIBindings.insert({TK_UP, UpMenu});*/

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

