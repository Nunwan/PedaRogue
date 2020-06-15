//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine()
{
    mECSManager = std::make_shared<ECSManager>();
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
}


void Engine::initComponents()
{
    mECSManager->RegisterComponent<Render>();
    mECSManager->RegisterComponent<Transform>();
    mECSManager->RegisterComponent<Map>();
    mECSManager->RegisterComponent<Others>();
}


void Engine::render(std::shared_ptr<Window> window)
{
    window->clear();
    mRenderMapSystem->render(window);
    mRenderOthersSystem->render(window);
    window->refresh();
}
