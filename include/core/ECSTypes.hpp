//
// Created by nunwan on 08/06/2020.
//

#ifndef PEDAROGUE_ECSTYPES_HPP
#define PEDAROGUE_ECSTYPES_HPP
#include <cstdint>
#include <bitset>

// Entity is only an id so an int. 32 bits have to be enough
using Entity = uint32_t;

using ComponentType = uint8_t;

// Limit bitset length to 256 bc ComponentType is on 8 bits
using Signature = std::bitset<256>;

class System
{
private:
    std::set<Entity> mEntities;
public:
    const std::set<Entity> &getEntities() const;
};

const std::set<Entity> &System::getEntities() const
{
    return mEntities;
}

#endif //PEDAROGUE_ECSTYPES_HPP
