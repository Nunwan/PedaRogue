//
// Created by nunwan on 14/06/2020.
//

#include "Game.hpp"
#include "Components.hpp"


Game::Game()
{
    mEngine = std::make_unique<Engine>();
}


void Game::Init()
{
    mEngine->initComponents();
    mEngine->initSystems();
    Entity player = mEngine->mECSManager->CreateEntity();
    Transform posPlayer = {10, 10, 0};
    mEngine->mECSManager->AddComponent(player, posPlayer);
    Render renderPlayer = {"@"};
    mEngine->mECSManager->AddComponent(player, renderPlayer);
    mEngine->mECSManager->AddComponent(player, Others());
    mEngine->mECSManager->AddComponent(player, Playable());
    // Player 2 for test
    Entity player2= mEngine->mECSManager->CreateEntity();
    Transform posPlayer2= {20, 20, 0};
    mEngine->mECSManager->AddComponent(player2, posPlayer2);
    Render renderPlayer2= {"+"};
    mEngine->mECSManager->AddComponent(player2, renderPlayer2);
    mEngine->mECSManager->AddComponent(player2, Others());
}


void Game::run()
{
    int stop = 0;
    while (!stop) {
        mEngine->render();
        stop = mEngine->update();
    }
    terminal_close();
}
