//
// Created by nunwan on 16/06/2020.
//

#include <iostream>
#include "Level.hpp"
#include "Components.hpp"
#include "Engine.hpp"
#include "MonsterParse.hpp"
#include "FOVTools.hpp"

#define MONSTERPROBA 0.1f

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
    auto levelGen = LevelGeneration(HEIGHT_MAP, WIDTH_MAP, MONSTERPROBA, mLevelnumber / 50, 5);
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
            else if (type == FLOOR_LIGHT) {
                ConfigFloorLight(mMap[i][j], j, i);
            }
            else if (type == MONSTER) {
                ConfigFloor(mMap[i][j], j, i);
                ConfigMonster(j, i);
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
    RigidBody entityBody = {true, true};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, entityBody);
}


const Transform &Level::getBeginMap() const
{
    return beginMap;
}


void Level::ConfigFloorLight(Entity entity, int x, int y)
{
    Transform entityPos = {x, y, mLevelnumber};
    Render entityRender = {".", mEngine->getMWindow()->color_red, false};
    Stats statWall;
    statWall.stats["visibility"] = 5;
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, Light());
    mEngine->AddComponent(entity, statWall);

}


void Level::ConfigMonster(int x, int y)
{
    auto entity = mEngine->CreateEntity();
    MonsterParse monsterParse;
    // We roll a random Monster
    monsterParse.singleRandomMonster();
    Transform entityPos = {x, y, mLevelnumber};
    // Get the glyph from json object
    auto glyph = monsterParse.getMMonsterGlyph();
    char* glyphc = new char[glyph.size() + 1];
    std::copy(glyph.begin(), glyph.end(), glyphc);
    glyphc[glyph.size()] = '\0';
    // Get the color
    int r = monsterParse.getMMonsterColorR();
    int g = monsterParse.getMMonsterColorG();
    int b = monsterParse.getMMonsterColorB();
    Render entityRender = {glyphc, color_from_argb(0xff, r, g, b), false};
    Stats statMonster;
    auto statToPush = monsterParse.getMMonsterStat();
    for (std::pair<std::string, int> element : statToPush)
    {
        statMonster.stats[element.first] = element.second;
    }
    RigidBody entityRigid = {false, false};
    mEngine->AddComponent(entity, entityPos);
    mEngine->AddComponent(entity, entityRender);
    mEngine->AddComponent(entity, statMonster);
    mEngine->AddComponent(entity, entityRigid);
    mEngine->AddComponent(entity, Living());
    mMobs.push_back(entity);
}


