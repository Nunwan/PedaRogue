//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine()
{
    mWindow = std::make_shared<Window>();
}


void Engine::initSystems()
{
    mRenderMapSystem = RegisterSystem<RenderMapSystem>(this);
    UseComponent<RenderMapSystem, Map>();
    UseComponent<RenderMapSystem, Transform>();
    UseComponent<RenderMapSystem, Render>();
    mRenderOthersSystem = RegisterSystem<RenderOthersSystem>(this);
    UseComponent<RenderOthersSystem, Transform>();
    UseComponent<RenderOthersSystem, Render>();
    mInputHandler = RegisterSystem<InputHandler>(this);
    mInputHandler->Init();
}


void Engine::initComponents()
{
    RegisterComponent<Render>();
    RegisterComponent<Transform>();
    RegisterComponent<Map>();
    RegisterComponent<NotMap>();
    RegisterComponent<Playable>();
}


void Engine::render()
{
    mWindow->clear();
    mRenderMapSystem->render();
    mRenderOthersSystem->render();
    mWindow->refresh();
}


int Engine::update()
{
    mWindow->nextEvent(0, true);
    return mInputHandler->process_key(mWindow->event);
}


const std::shared_ptr<Window> &Engine::getMWindow() const
{
    return mWindow;
}
