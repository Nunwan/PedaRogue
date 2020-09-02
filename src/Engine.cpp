//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine(Game* game)
{
    mWindow = std::make_shared<Window>();
    mUI = UI(mWindow);
    mGame = game;
}


void Engine::initSystems()
{
    mRenderSystems.insert({typeid(RenderMapSystem).name(), RegisterSystem<RenderMapSystem>(this)});
    UseComponent<RenderMapSystem, Map>();
    UseComponent<RenderMapSystem, Transform>();
    UseComponent<RenderMapSystem, Render>();
    mRenderSystems.insert({typeid(RenderOthersSystem).name(), RegisterSystem<RenderOthersSystem>(this)});
    UseComponent<RenderOthersSystem, Transform>();
    UseComponent<RenderOthersSystem, Render>();
    UseComponent<RenderOthersSystem, NotMap>();
    mInputHandler = RegisterSystem<InputHandler>(this);
    mUpdateSystems.insert({typeid(CollisionSystem).name(), RegisterSystem<CollisionSystem>(this)});
    UseComponent<CollisionSystem, Transform>();
    UseComponent<CollisionSystem, RigidBody>();
    mUpdateSystems.insert({typeid(BackSystem).name(), RegisterSystem<BackSystem>(this)});
    UseComponent<BackSystem, BackAttempt>();
    mUpdateSystems.insert({typeid(FoVCompute).name(), RegisterSystem<FoVCompute>(this)});
    UseComponent<FoVCompute, Transform>();
    UseComponent<FoVCompute, Playable>();
    UseComponent<FoVCompute, Stats>();
    mUpdateSystems.insert({typeid(LightSystem).name(), RegisterSystem<LightSystem>(this)});
    UseComponent<LightSystem, Transform>();
    UseComponent<LightSystem, Light>();
    UseComponent<LightSystem, Stats>();
    mUpdateSystems.insert({typeid(AttackSystem).name(), RegisterSystem<AttackSystem>(this)});
    UseComponent<AttackSystem, AttackAttempt>();
    mUpdateSystems.insert({typeid(PickSystem).name(), RegisterSystem<PickSystem>(this)});
    UseComponent<PickSystem, PickAttempt>();
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
    RegisterComponent<Object>();
    RegisterComponent<PickAttempt>();
    RegisterComponent<Container>();
    RegisterComponent<Namable>();
    RegisterComponent<Stairway>();
    RegisterComponent<BackAttempt>();
}


void Engine::render()
{
    mWindow->select_win(WIN_JEU);
    mWindow->clear();
    for (const auto& system : mRenderSystems) {
        system.second->render();
    }
    mWindow->refresh();
    // Render status bar
    auto& playerStat = GetComponent<Stats>(GetPlayer());
    mUI.render_status_bar(playerStat);
    mUI.newTurn();
}


int Engine::update()
{
    mWindow->select_win(WIN_MSG);
    mWindow->clear();
    mWindow->nextEvent(0, true);
    int finish = mInputHandler->process_key(mWindow->event);
    process_event(this);
    for (const auto& system : mUpdateSystems) {
        system.second->update();
    }
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
            if (HasComponent<Map>(map[i][j])) {
                DelComponent<Map>(map[i][j]);
            }
        }
    }
    for (auto const& entity : level->getMObjects()) {
        if (HasComponent<NotMap>(entity)) {
            DelComponent<NotMap>(entity);
        }
    }
    for (auto const& entity : level->getMMobs()) {
        if (HasComponent<NotMap>(entity)) {
            DelComponent<NotMap>(entity);
        }
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
    return GetLevel(levelnumber)->getMMap()[y][x];
}


bool Engine::check_event()
{
    return mEvents.size() != 0;
}


void Engine::create_level()
{
    mGame->create_level();
    mNbLvl++;
}


std::shared_ptr<CollisionSystem> Engine::getCollisionSystem()
{
    return std::static_pointer_cast<CollisionSystem>(mUpdateSystems[typeid(CollisionSystem).name()]);
}
