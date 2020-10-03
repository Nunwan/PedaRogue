//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine(Game* game)
{
    mWindow = std::make_shared<Window>();
    mUI = UI(mWindow);
    mGame = game;
    mCommandProcessor = RegisterSystem<CommandProcessor>(this);
}


void Engine::initSystems()
{
    mUpdateSystemPlacement.insert({typeid(CollisionSystem).name(), 1});

    mRenderSystems.push_back(RegisterSystem<RenderMapSystem>(this));
    UseComponent<RenderMapSystem, Map>();
    UseComponent<RenderMapSystem, Transform>();
    UseComponent<RenderMapSystem, Render>();
    mRenderSystems.push_back(RegisterSystem<RenderOthersSystem>(this));
    UseComponent<RenderOthersSystem, Transform>();
    UseComponent<RenderOthersSystem, Render>();
    UseComponent<RenderOthersSystem, NotMap>();
    mInputHandler = RegisterSystem<InputHandler>(this);
    mUpdateSystems.push_back(RegisterSystem<PlayerMovement>(this));
    UseComponent<PlayerMovement, Playable>();
    UseComponent<PlayerMovement, Transform>();
    UseComponent<PlayerMovement, NotMap>();
    UseComponent<PlayerMovement, Render>();
    UseComponent<PlayerMovement, Moveable>();
    UseComponent<PlayerMovement, to_Move>();
    mUpdateSystems.push_back(RegisterSystem<CollisionSystem>(this));
    UseComponent<CollisionSystem, Transform>();
    UseComponent<CollisionSystem, RigidBody>();
    mUpdateSystems.push_back(RegisterSystem<BackSystem>(this));
    UseComponent<BackSystem, BackAttempt>();
    mUpdateSystems.push_back(RegisterSystem<FoVCompute>(this));
    UseComponent<FoVCompute, Transform>();
    UseComponent<FoVCompute, Playable>();
    UseComponent<FoVCompute, Stats>();
    mUpdateSystems.push_back(RegisterSystem<LightSystem>(this));
    UseComponent<LightSystem, Transform>();
    UseComponent<LightSystem, Light>();
    UseComponent<LightSystem, Stats>();
    mUpdateSystems.push_back(RegisterSystem<AttackSystem>(this));
    UseComponent<AttackSystem, AttackAttempt>();
    mUpdateSystems.push_back(RegisterSystem<PickSystem>(this));
    UseComponent<PickSystem, PickAttempt>();

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
    RegisterComponent<to_Move>();
}


void Engine::render()
{
    mWindow->select_win(WIN_JEU);
    mWindow->clear();
    for (const auto& system : mRenderSystems) {
        system->render();
    }
    mWindow->refresh();
    // Render status bar
    auto& playerStat = GetComponent<Stats>(GetPlayer());
    mUI.render_status_bar(playerStat);
    mUI.render();
    mUI.newTurn();
}


int Engine::update()
{
    mWindow->select_win(WIN_MSG);
    mWindow->clear();
    mWindow->nextEvent(0, true);
    int finish = mInputHandler->process_key(mWindow->event);
    mCommandProcessor->process();
    for (const auto& system : mUpdateSystems) {
        system->update();
        process_event(this);
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
    return std::static_pointer_cast<CollisionSystem>(mUpdateSystems[mUpdateSystemPlacement[typeid(CollisionSystem).name()]]);
}


std::shared_ptr<Inventory> Engine::getMInventoryPlayerSystem()
{
    return mInventoryPlayerSystem;
}


void Engine::initInventory()
{
    std::string title = "Your Inventory";
    mInventoryPlayerSystem = std::make_shared<Inventory>(GetPlayer(), this, title);
}


void Engine::pushCommand(Command *command)
{
    mCommandProcessor->pushCommand(command);

}


void Engine::initAfterPersoCreation()
{
    mInputHandler->Init();

}
