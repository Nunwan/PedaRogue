//
// Created by nunwan on 16/06/2020.
//

#include "Level.hpp"


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


Level::Level()
{
    mMap = new Entity*[HEIGHT_MAP];
    for (int i = 0; i < HEIGHT_MAP; i++) {
        mMap[i] = new Entity[WIDTH_MAP];
    }
}


Level::~Level()
{
    for (int i = 0; i < HEIGHT_MAP; i++) {
        delete mMap[i];
    }
    delete mMap;
}

