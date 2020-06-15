//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine()
{
    mECSManager = std::make_shared<ECSManager>();
    mWindow = std::make_shared<Window>();
}


void Engine::initSystems()
{
    mRenderMapSystem = mECSManager->RegisterSystem<RenderMapSystem>();
    mECSManager->UseComponent<RenderMapSystem, Map>();
    mECSManager->UseComponent<RenderMapSystem, Transform>();
    mECSManager->UseComponent<RenderMapSystem, Render>();
    mRenderOthersSystem = mECSManager->RegisterSystem<RenderOthersSystem>();
    mECSManager->UseComponent<RenderOthersSystem, Transform>();
    mECSManager->UseComponent<RenderOthersSystem, Render>();
    mInputHandler = mECSManager->RegisterSystem<InputHandler>();
    mInputHandler->Init();
}


void Engine::initComponents()
{
    mECSManager->RegisterComponent<Render>();
    mECSManager->RegisterComponent<Transform>();
    mECSManager->RegisterComponent<Map>();
    mECSManager->RegisterComponent<Others>();
    mECSManager->RegisterComponent<Playable>();
}


void Engine::render()
{
    mWindow->clear();
    mRenderMapSystem->render(mWindow);
    mRenderOthersSystem->render(mWindow);
    mWindow->refresh();
}


int Engine::update()
{
    mWindow->nextEvent(0, true);
    return mInputHandler->process_key(mWindow->event);
}
