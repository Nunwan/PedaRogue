//
// Created by nunwan on 09/06/2020.
//

#ifndef PEDAROGUE_COMPONENTPOOL_HPP
#define PEDAROGUE_COMPONENTPOOL_HPP
#include <vector>
#include "ECSTypes.hpp"

template<typename T>
class ComponentPool {
private:
    std::vector<T> packed;
    std::vector<int> sparse;
    std::vector<Entity> packedId;

public:
    ComponentPool() = default;
    virtual ~ComponentPool() = default;

    void link(Entity entity, T component);
    void unlink(Entity entity);

    bool exist(Entity entity);
    T& Get(Entity entity);

    //Iterators
    typename std::vector<T>::iterator iterBeginComp();
    typename std::vector<T>::iterator iterEndComp();

    // Getters
    const std::vector<Entity> &getPackedId() const;

    const std::vector<T> &getPacked() const;

    const std::vector<int> &getSparse() const;

};


template<typename T>
void ComponentPool<T>::link(Entity entity, T component)
{
    if (sparse.size() <= entity) {
        sparse.resize(entity+1);
    }
    sparse[entity] = packed.size();
    packed.push_back(component);
    packedId.push_back(entity);
}


template<typename T>
void ComponentPool<T>::unlink(Entity entity)
{
    assert(entity < sparse.size() && packedId[sparse[entity]] == entity);
    Entity entity_back = packedId.back();
    T to_unlink;
    to_unlink = packed[sparse[entity]];
    sparse[entity_back] = sparse[entity];
    packed[sparse[entity]] = packed.back();
    packed.back() = to_unlink;
    packed.pop_back();
    packedId[sparse[entity]] = -1;
    sparse[entity] = -1;
}


template<typename T>
T& ComponentPool<T>::Get(Entity entity)
{
    assert(entity < sparse.size() && packedId[sparse[entity]] == entity);
    return packed[sparse[entity]];
}


template<typename T>
bool ComponentPool<T>::exist(Entity entity)
{
    return entity < sparse.size() && packedId[sparse[entity]] == entity;
}


template<typename T>
const std::vector<Entity> &ComponentPool<T>::getPackedId() const
{
    return packedId;
}


template<typename T>
const std::vector<T> &ComponentPool<T>::getPacked() const
{
    return packed;
}


template<typename T>
const std::vector<int> &ComponentPool<T>::getSparse() const
{
    return sparse;
}


template<typename T>
typename std::vector<T>::iterator ComponentPool<T>::iterBeginComp()
{
    return packed.begin();
}


template<typename T>
typename std::vector<T>::iterator ComponentPool<T>::iterEndComp()
{
    return packed.end();
}

#endif //PEDAROGUE_COMPONENTPOOL_HPP
