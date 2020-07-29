//
// Created by nunwan on 14/06/2020.
//

#include "Game.hpp"
#include "Components.hpp"


Game::Game()
{
    mEngine = std::make_unique<Engine>(this);
}


void Game::Init()
{
    mEngine->initComponents();
    mEngine->initSystems();
    mLevels.push_back(std::make_shared<Level>(0, mEngine.get()));
    mLevels[0]->GenerateMap();
    mEngine->level_enable(mLevels[0]);
    PlayerCreation();
}


void Game::run()
{
    int stop = 0;
    while (!stop) {
        stop = mEngine->update();
        mEngine->render();
    }
    close();
}


void Game::close()
{
    terminal_close();
}


const vector<std::shared_ptr<Level>> &Game::getMLevels() const
{
    return mLevels;
}


void Game::PlayerCreation()
{
    Entity player = mEngine->CreateEntity();
    mEngine->AddComponent(player, mLevels[0]->getBeginMap());
    Render renderPlayer = {"@", mEngine->getMWindow()->color_yellow, true};
    mEngine->AddComponent(player, renderPlayer);
    mEngine->AddComponent(player, NotMap());
    Moveable playerMove = {DIR_LEFT};
    mEngine->AddComponent(player, playerMove);
    mEngine->AddComponent(player, Playable());
    mEngine->AddComponent(player, Living());
    RigidBody rigidPlayer = {false, false};
    mEngine->AddComponent(player, rigidPlayer);
    Stats statPlayer;
    statPlayer.stats["visibility"] = 5;
    mEngine->AddComponent(player, statPlayer);
    mPlayerLocalId = mPlayers.size();
    mPlayers.push_back(player);
}
