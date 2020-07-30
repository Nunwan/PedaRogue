//
// Created by nunwan on 16/06/2020.
//

#ifndef PEDAROGUE_LEVEL_HPP
#define PEDAROGUE_LEVEL_HPP

#include <vector>
#include "core/ECSTypes.hpp"
#include "LevelGeneration.hpp"
#include "Components.hpp"

#define HEIGHT_MAP 200
#define WIDTH_MAP 200

class Level
{
public:
    // Getters
    const Transform &getBeginMap() const;

    const std::vector<Entity> &getMObjects() const;

    const std::vector<Entity> &getMMobs() const;

    Entity **getMMap() const;

    virtual ~Level();

    Level(int levelnumber, Engine* engine);

    /**
     * @brief       generate the map with a random generation which will create a new map
     */
    void GenerateMap();



private:
    Engine* mEngine;
    int mLevelnumber;
    Entity** mMap;
    std::vector<Entity> mObjects;
    std::vector<Entity> mMobs;
    Transform beginMap;

    /**
     * @brief               Take a generation of a level and create the adequate entity
     * @param levelGen      The level generation object which contains map data
     */
    void CreateMap(LevelGeneration& levelGen);

    /* Configuration of each type of tile in the map : create entity and add component */
    void ConfigFloor(Entity entity, int x, int y);
    void ConfigWall(Entity entity, int x, int y);
    void ConfigFloorLight(Entity entity, int x, int y);
    void ConfigWallTunnel(Entity entity, int x, int y);
    void ConfigDoor(Entity entity, int x, int y);
    void ConfigMonster(int x, int y);
    void ConfigObject(int x, int y);
};


#endif //PEDAROGUE_LEVEL_HPP
