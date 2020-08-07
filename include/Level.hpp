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

    Entity getMStairwayUp() const;

    Entity getMStairwayDown() const;


    // Constructors & Getters
    Level(int levelnumber, Engine* engine);
    virtual ~Level();

    /**
     * @brief       generate the map with a random generation which will create a new map
     */
    void GenerateMap();


private:
    Engine* mEngine;
    int mLevelnumber;
    Entity** mMap;
    int** mToGenerate;
    std::vector<Entity> mObjects;
    std::vector<Entity> mMobs;
    Transform beginMap;
    Entity mStairwayUp, mStairwayDown;

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
    void ConfigStairwayDown(Entity entity, int x, int y);
    void ConfigStairwayUp(Entity entity, int x, int y);
    void ConfigMonster(int x, int y);
    void ConfigObject(int x, int y);
};


#endif //PEDAROGUE_LEVEL_HPP
