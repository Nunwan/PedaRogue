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
