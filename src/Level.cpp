//
// Created by nunwan on 16/06/2020.
//

#include "Level.hpp"
#include "Components.hpp"
#include "Engine.hpp"
#include "FOVTools.hpp"


const std::vector<Entity> &Level::getMObjects() const
{
    return mObjects;
}


const std::vector<Entity> &Level::getMMobs() const
{
    return mMobs;
}


Entity** Level::getMMap() const
{
    return mMap;
}


Level::Level(int levelnumber, Engine* engine)
{
    mEngine = engine;
    mLevelnumber = levelnumber;
    mMap = new Entity*[HEIGHT_MAP];
    for (int i = 0; i < HEIGHT_MAP; i++) {
        mMap[i] = new Entity[WIDTH_MAP];
    }
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            mMap[i][j] = mEngine->CreateEntity();
        }
    }
}


Level::~Level()
{
    for (int i = 0; i < HEIGHT_MAP; i++) {
        delete[] mMap[i];
    }
     delete[] mMap;
}


void Level::GenerateMap()
{
    auto levelGen = LevelGeneration(HEIGHT_MAP, WIDTH_MAP);
    levelGen.run();
    if (mLevelnumber == 0) {
        levelGen.place_player(&beginMap);
    }
    CreateMap(levelGen);
}


void Level::CreateMap(LevelGeneration& levelGen)
{
    int** mapToGenerate = levelGen.getMToGenerate();
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            int type = mapToGenerate[i][j];
            if (type == FLOOR) {
                ConfigFloor(mMap[i][j], j, i);
            }
            else if (type == WALL) {
                ConfigWall(mMap[i][j], j, i);
            }
            else if (type == WALL_TUNNEL) {
                ConfigWallTunnel(mMap[i][j], j, i);
            }
            else if (type == DOOR) {
                ConfigDoor(mMap[i][j], j, i);
            }
            else if (type == 6) {
                auto entity = mMap[i][j];
                Transform entityPos = {j, i, mLevelnumber};
                Render entityRender = {"T", mEngine->getMWindow()->color_white};
                RigidBody entityBody = {true};
                mEngine->AddComponent(entity, entityPos);
                mEngine->AddComponent(entity, entityRender);
                mEngine->AddComponent(entity, entityBody);
            }
        }
    }
}


void Level::ConfigFloor(Entity entity, int x, int y)
{
    Transform entityPos = {x, y, mLevelnumber};
    Render entityRender = {".", mEngine->getMWindow()->color_white, false};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
}


void Level::ConfigWall(Entity entity, int x, int y)
{
    Transform entityPos = {x, y, mLevelnumber};
    Render entityRender = {"#", mEngine->getMWindow()->color_white, false};
    RigidBody entityBody = {false, false};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, entityBody);
}


void Level::ConfigWallTunnel(Entity entity, int x, int y)
{
    Transform entityPos = {x, y, mLevelnumber};
    Render entityRender = {"#", mEngine->getMWindow()->color_blue, false};
    RigidBody entityBody = {false};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, entityBody);
}


void Level::ConfigDoor(Entity entity, int x, int y)
{
    Transform entityPos = {x, y, mLevelnumber};
    Render entityRender = {"-", mEngine->getMWindow()->color_white, false};
    RigidBody entityBody = {true, false};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, entityBody);
}


const Transform &Level::getBeginMap() const
{
    return beginMap;
}


void Level::ComputeFOV(int x, int y, int range)
{
#if DEBUG_MODE_FOV == 1
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            auto& entity = mMap[i][j];
            if (mEngine->HasComponent<Render>(entity)) {
                auto& entityRender = mEngine->GetComponent<Render>(entity);
                entityRender.color = mEngine->getMWindow()->color_white;
            }
        }

    }
#endif
    std::vector<Transform> pointCircle;
    almost_circle(pointCircle, x, y, WIDTH_MAP, HEIGHT_MAP, range);

    for (auto const& point : pointCircle) {
        Line(x, y, point.x, point.y, this);
    }
#if DEBUG_MODE_FOV == 1
    for (auto const& point : pointCircle) {
        auto& entity = mMap[point.y][point.x];
        if (mEngine->HasComponent<Render>(entity)) {
            auto& entityRender = mEngine->GetComponent<Render>(entity);
            entityRender.color = mEngine->getMWindow()->color_red;
        }
    }
#endif
}


int Level::to_display(int x, int y)
{
    Entity& entity = mMap[y][x];
    if (mEngine->HasComponent<Render>(entity)) {
        auto &entityRender = mEngine->GetComponent<Render>(entity);
#if DEBUG_MODE_FOV == 1
        entityRender.color = mEngine->getMWindow()->color_blue;
#endif
        entityRender.to_display = true;
    }
    if (mEngine->HasComponent<RigidBody>(entity)) {
        auto& entityRigid = mEngine->GetComponent<RigidBody>(entity);
        return !entityRigid.transparent;
    }
    return false;
}

