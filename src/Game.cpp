//
// Created by nunwan on 14/06/2020.
//

#include "Game.hpp"
#include "Components.hpp"


Game::Game()
{
    mEngine = std::make_unique<Engine>();
    mWindow = std::make_shared<Window>();
}


void Game::Init()
{
    mEngine->initComponents();
    mEngine->initSystems();
    Entity player = mEngine->mECSManager->CreateEntity();
    Transform posPlayer = {10, 10, 0};
    mEngine->mECSManager->AddComponent(player, posPlayer);
    Render renderPlayer = {'@', TCODColor::amber};
    mEngine->mECSManager->AddComponent(player, renderPlayer);
    mEngine->mECSManager->AddComponent(player, Others());
    Entity player2= mEngine->mECSManager->CreateEntity();
    Transform posPlayer2= {20, 20, 0};
    mEngine->mECSManager->AddComponent(player2, posPlayer2);
    Render renderPlayer2= {'+', TCODColor::amber};
    mEngine->mECSManager->AddComponent(player2, renderPlayer2);
    mEngine->mECSManager->AddComponent(player2, Others());
}


void Game::run()
{
    while (true) {
        if (mWindow->event.eventtype == TCOD_EVENT_KEY_RELEASE && mWindow->event.key.vk == TCODK_ESCAPE) {
            break;
        }
        mEngine->render(mWindow);
        mWindow->nextEvent(TCOD_EVENT_ANY, true);
    }
}
