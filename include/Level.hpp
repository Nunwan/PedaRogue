//
// Created by nunwan on 16/06/2020.
//

#ifndef PEDAROGUE_LEVEL_HPP
#define PEDAROGUE_LEVEL_HPP

#include <vector>
#include "core/ECSTypes.hpp"

#define HEIGHT_MAP 200
#define WIDTH_MAP 200

class Level
{
public:
    const std::vector<Entity> &getMObjects() const;

    const std::vector<Entity> &getMMobs() const;

    Entity **getMMap() const;

    virtual ~Level();

    Level();

private:
    Entity** mMap;
    std::vector<Entity> mObjects;
    std::vector<Entity> mMobs;
};


#endif //PEDAROGUE_LEVEL_HPP
