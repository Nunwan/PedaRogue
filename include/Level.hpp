//
// Created by nunwan on 16/06/2020.
//

#ifndef PEDAROGUE_LEVEL_HPP
#define PEDAROGUE_LEVEL_HPP

#include <vector>
#include "core/ECSTypes.hpp"
#include "LevelGeneration.hpp"

#define HEIGHT_MAP 200
#define WIDTH_MAP 200

class Level
{
public:
    const std::vector<Entity> &getMObjects() const;

    const std::vector<Entity> &getMMobs() const;

    Entity **getMMap() const;

    virtual ~Level();

    Level(int levelnumber, Engine* engine);

    void GenerateMap();

private:
    Engine* mEngine;
    int mLevelnumber;
    Entity** mMap;
    std::vector<Entity> mObjects;
    std::vector<Entity> mMobs;

    void CreateMap(LevelGeneration& levelGen);

    void ConfigFloor(Entity entity, int x, int y);
    void ConfigWall(Entity entity, int x, int y);
    void ConfigDoor(Entity entity, int x, int y);
};


#endif //PEDAROGUE_LEVEL_HPP
