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
    Entity player = mEngine->CreateEntity();
    Transform posPlayer = {10, 10, 0};
    mEngine->AddComponent(player, posPlayer);
    Render renderPlayer = {"@", mEngine->getMWindow()->color_blue};
    mEngine->AddComponent(player, renderPlayer);
    mEngine->AddComponent(player, NotMap());
    mEngine->AddComponent(player, Playable());
    // Player 2 for test
    Entity player2= mEngine->CreateEntity();
    Transform posPlayer2= {20, 20, 0};
    mEngine->AddComponent(player2, posPlayer2);
    Render renderPlayer2= {"+", mEngine->getMWindow()->color_white};
    mEngine->AddComponent(player2, renderPlayer2);
    mEngine->AddComponent(player2, NotMap());
}


void Game::run()
{
    int stop = 0;
    while (!stop) {
        mEngine->render();
        stop = mEngine->update();
    }
    close();
}


void Game::close()
{
    terminal_close();
}
