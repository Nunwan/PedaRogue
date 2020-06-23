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
    mLevels.push_back(std::make_shared<Level>(0, mEngine.get()));
    mLevels[0]->GenerateMap();
    mEngine->level_enable(mLevels[0]);
    Entity player = mEngine->CreateEntity();
    mEngine->AddComponent(player, mLevels[0]->getBeginMap());
    Render renderPlayer = {"@", mEngine->getMWindow()->color_blue};
    mEngine->AddComponent(player, renderPlayer);
    mEngine->AddComponent(player, NotMap());
    Moveable playerMove = {DIR_LEFT};
    mEngine->AddComponent(player, playerMove);
    mEngine->AddComponent(player, Playable());
    RigidBody rigidPlayer = {false, false};
    mEngine->AddComponent(player, rigidPlayer);
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
