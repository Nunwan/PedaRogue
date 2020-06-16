//
// Created by nunwan on 08/06/2020.
//

#ifndef PEDAROGUE_ECSTYPES_HPP
#define PEDAROGUE_ECSTYPES_HPP
#include <cstdint>
#include <bitset>
#include <set>
#include <memory>

// Entity is only an id so an int. 32 bits have to be enough
using Entity = uint32_t;

using ComponentType = uint8_t;

// Limit bitset length to 256 bc ComponentType is on 8 bits
using Signature = std::bitset<256>;

class Engine;
class System
{
public:
    Engine* mEngine;
    std::set<Entity> mEntities;
    std::set<Entity> &getEntities()
    {
        return mEntities;
    }
    void registerManager(Engine* engine)
    {
        mEngine = engine;
    }

};




#endif //PEDAROGUE_ECSTYPES_HPP
