//
// Created by nunwan on 16/06/2020.
//

#ifndef PEDAROGUE_LEVEL_HPP
#define PEDAROGUE_LEVEL_HPP

#include <vector>
#include "core/ECSTypes.hpp"
#include "LevelGeneration.hpp"
#include "Components.hpp"

#define HEIGHT_MAP 40
#define WIDTH_MAP 120

class Level
{
public:
    const std::vector<Entity> &getMObjects() const;

    const std::vector<Entity> &getMMobs() const;

    Entity **getMMap() const;

    virtual ~Level();

    Level(int levelnumber, Engine* engine);

    void GenerateMap();

    const Transform &getBeginMap() const;

    void ComputeFOV(int x, int y, int range);
    int to_display(int x, int y);

private:
    Engine* mEngine;
    int mLevelnumber;
    Entity** mMap;
    std::vector<Entity> mObjects;
    std::vector<Entity> mMobs;
    Transform beginMap;

    void CreateMap(LevelGeneration& levelGen);

    void ConfigFloor(Entity entity, int x, int y);
    void ConfigWall(Entity entity, int x, int y);
    void ConfigWallTunnel(Entity entity, int x, int y);
    void ConfigDoor(Entity entity, int x, int y);



};


#endif //PEDAROGUE_LEVEL_HPP
