//
// Created by nunwan on 09/06/2020.
//

#ifndef PEDAROGUE_COMPONENTPOOL_HPP
#define PEDAROGUE_COMPONENTPOOL_HPP
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include "ECSTypes.hpp"

/**
 * @brief   Virtual Interface of Component Pool to always have Entity Destroyed
 */
class IComponentPool {
public:
    /**
     * @brief           Tell to the Pool that entity was destroyed
     * @param entity    Entity which has been destroyed
     */
    virtual void EntityDestroyed(Entity entity) = 0;
};

/**
 * @brief       Component Pool to save components of a given type
 *              The Pool works as a sparse array. the sparse and reverseSparse give coordinate and inverted coordinated
 *              of the component of the entity in packed.
 *              Packed is a continous vector of components of type T.
 * @tparam T    Type of component to save
 */
template<typename T>
class ComponentPool :public IComponentPool
{
private:
    std::vector<T> packed;
    std::unordered_map<Entity, int> sparse;
    std::unordered_map<int, Entity> reverseSparse;

public:

    /**
     * @brief               Link an entity to its new component
     * @param entity        Entity which gonna has a new component
     * @param component     The new component
     */
    void link(Entity entity, T component);

    /**
     * @brief               Unlink an entity to the component previously linked
     * @param entity        Entity which will have a component deleted
     */
    void unlink(Entity entity);

    /**
     * @brief               Check if an entity has a component in this pool
     * @param entity        The entity to verify
     * @return              1 if component exist 0 if not
     */
    bool exist(Entity entity);

    /**
     * @brief               Return reference to the component for the entity
     * @param entity        Entity which wants its component
     * @return              Reference to the given component
     */
    T& Get(Entity entity);

    void EntityDestroyed(Entity entity) override;

    //Iterators
    /**
     * @return      begin of iterator of the components of type T
     */
    typename std::vector<T>::iterator iterBeginComp();

    /**
     * @return      End of the iterator of the components of type T
     */
    typename std::vector<T>::iterator iterEndComp();

    // Getters
    const std::vector<T> &getPacked() const;

    const std::unordered_map<Entity, int> &getSparse() const;


};


template<typename T>
void ComponentPool<T>::link(Entity entity, T component)
{
    sparse.insert({entity, packed.size()});
    reverseSparse.insert({packed.size(), entity});
    packed.push_back(component);
    assert(entity == reverseSparse[sparse[entity]]);
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
    reverseSparse[sparse[entity_back]] = entity_back;
    reverseSparse.erase(packed.size() - 1);
    packed.pop_back();
    sparse.erase(entity);
}


template<typename T>
T& ComponentPool<T>::Get(Entity entity)
{
    assert(sparse.count(entity));
    assert(packed.size() > sparse[entity]);
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
