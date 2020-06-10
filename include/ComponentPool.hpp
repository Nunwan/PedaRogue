//
// Created by nunwan on 09/06/2020.
//

#ifndef PEDAROGUE_COMPONENTPOOL_HPP
#define PEDAROGUE_COMPONENTPOOL_HPP
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include "ECSTypes.hpp"

class IComponentPool {
public:
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentPool :public IComponentPool
{
private:
    std::vector<T> packed;
    std::unordered_map<Entity, int> sparse;
    std::unordered_map<int, Entity> reverseSparse;

public:

    void link(Entity entity, T component);
    void unlink(Entity entity);

    bool exist(Entity entity);
    T& Get(Entity entity);

    //Iterators
    typename std::vector<T>::iterator iterBeginComp();
    typename std::vector<T>::iterator iterEndComp();

    // Getters
    const std::vector<T> &getPacked() const;

    const std::unordered_map<Entity, int> &getSparse() const;

    void EntityDestroyed(Entity entity) override;

};


template<typename T>
void ComponentPool<T>::link(Entity entity, T component)
{
    sparse.insert({entity, packed.size()});
    reverseSparse.insert({packed.size(), entity});
    packed.push_back(component);
}


template<typename T>
void ComponentPool<T>::unlink(Entity entity)
{
    assert(sparse.count(entity));
    Entity entity_back = reverseSparse[packed.size() -1];
    reverseSparse.erase(sparse[entity]);
    T to_unlink;
    to_unlink = packed[sparse[entity]];
    sparse[entity_back] = sparse[entity];
    packed[sparse[entity]] = packed.back();
    packed.back() = to_unlink;
    packed.pop_back();
    sparse.erase(entity);
}


template<typename T>
T& ComponentPool<T>::Get(Entity entity)
{
    assert(sparse.count(entity));
    return packed[sparse[entity]];
}


template<typename T>
bool ComponentPool<T>::exist(Entity entity)
{
    return sparse.count(entity);
}


template<typename T>
const std::vector<T> &ComponentPool<T>::getPacked() const
{
    return packed;
}


template<typename T>
const std::unordered_map<Entity, int> &ComponentPool<T>::getSparse() const
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

template<typename T>
void ComponentPool<T>::EntityDestroyed(Entity entity)
{
    if (this->exist(entity))
    {
        this->unlink(entity);
    }
}

#endif //PEDAROGUE_COMPONENTPOOL_HPP
