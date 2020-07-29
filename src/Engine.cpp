//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine(Game* game)
{
    mWindow = std::make_shared<Window>();
    mGame = game;
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
    UseComponent<RenderOthersSystem, NotMap>();
    mInputHandler = RegisterSystem<InputHandler>(this);
    mCollisionSystem = RegisterSystem<CollisionSystem>(this);
    UseComponent<CollisionSystem, Transform>();
    UseComponent<CollisionSystem, RigidBody>();
    mFovComputeSystem = RegisterSystem<FoVCompute>(this);
    UseComponent<FoVCompute, Transform>();
    UseComponent<FoVCompute, Playable>();
    UseComponent<FoVCompute, Stats>();
    mLightSystem = RegisterSystem<LightSystem>(this);
    UseComponent<LightSystem, Transform>();
    UseComponent<LightSystem, Light>();
    UseComponent<LightSystem, Stats>();
    mAttackSystem = RegisterSystem<AttackSystem>(this);
    UseComponent<AttackSystem, AttackAttempt>();
    mInputHandler->Init();
}


void Engine::initComponents()
{
    RegisterComponent<Render>();
    RegisterComponent<Transform>();
    RegisterComponent<Map>();
    RegisterComponent<NotMap>();
    RegisterComponent<Playable>();
    RegisterComponent<RigidBody>();
    RegisterComponent<Moveable>();
    RegisterComponent<Stats>();
    RegisterComponent<Light>();
    RegisterComponent<Living>();
    RegisterComponent<AttackAttempt>();
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
    int finish = mInputHandler->process_key(mWindow->event);
    process_event(this);
    mAttackSystem->update();
    mFovComputeSystem->compute();
    mLightSystem->compute();
    return finish;
}


const std::shared_ptr<Window> &Engine::getMWindow() const
{
    return mWindow;
}


void Engine::level_enable(std::shared_ptr<Level> level)
{
    Entity** map = level->getMMap();
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            AddComponent(map[i][j], Map());
        }
    }
    for (auto const& entity : level->getMObjects()) {
        AddComponent(entity, NotMap());
    }
    for (auto const& entity : level->getMMobs()) {
        AddComponent(entity, NotMap());
    }
}


void Engine::level_disable(std::shared_ptr<Level> level)
{
    Entity** map = level->getMMap();
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            DelComponent<Map>(map[i][j]);
        }
    }
    for (auto const& entity : level->getMObjects()) {
        DelComponent<NotMap>(entity);
    }
    for (auto const& entity : level->getMMobs()) {
        DelComponent<NotMap>(entity);
    }

}


std::shared_ptr<Level> Engine::GetLevel(int levelnumber)
{
    return mGame->getMLevels()[levelnumber];
}


Entity &Engine::GetPlayer()
{
    return mGame->mPlayers[mGame->mPlayerLocalId];
}


void Engine::push_Event(Event event)
{
    mEvents.push(event);
}


Event Engine::pop_event()
{
    auto event = mEvents.front();
    mEvents.pop();
    return event;
}


Entity &Engine::getEntityat(int x, int y, int levelnumber)
{
    return mGame->getMLevels()[levelnumber]->getMMap()[y][x];
}


bool Engine::check_event()
{
    return mEvents.size() != 0;
}
