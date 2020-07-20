//
// Created by nunwan on 09/06/2020.
//

#ifndef PEDAROGUE_COMPONENTMANAGER_HPP
#define PEDAROGUE_COMPONENTMANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>
#include "ComponentPool.hpp"
#include "EntityManager.hpp"


/**
 * @brief   Manager of all components types : register, add, delete, check.
 *          The manager creates as many pools as registered components and make an interface for the creation and
 *          deletion of a certain type of components
 */
class ComponentManager
{
private:
    /**
     *  Map of the components pools : pools can be retrieve by the name of their ID type.
     */
    std::unordered_map<std::string, std::shared_ptr<IComponentPool>> mComponentsPools;
    /**
     *  Map of the types in order to has an integer which identify the component type.
     *  ID can be retrieve thanks to the name of their ID type.
     */
    std::unordered_map<std::string, ComponentType> mComponentTypes;
    /**
     *  Incremental ID to give the next possible component type ID
     */
    ComponentType mNextComponentType;

public:
    ComponentManager()
    {
        mNextComponentType = 0;
    }

    /**
     * @brief       Register the component : create the Pool, link it to the good name and ID.
     * @tparam T    Type of the new component
     */
    template<typename T>
    void RegisterComponent();

    /**
     * @brief               Link an entity and a component : select the pool and use link on this pool.
     * @tparam T            Type of the component
     * @param entity        Entity which will be linked to the component
     * @param component     Component to add with datas.
     */
    template<typename T>
    void AddComponent(Entity entity,T component);

    /**
     * @brief               Unlink an entity and a component : select the pool and use unlink on this pool
     * @tparam T            Type of the component to unlinked
     * @param entity        Entity which does not need te component
     */
    template<typename T>
    void DelComponent(Entity entity);

    /**
     * @brief               Return reference to the component of type T of the entity : choose the pool and Get
     * @tparam T            Type of the component to return
     * @param entity        Entity which wants its component of type T
     * @return              Reference to the selected component for the entity
     */
    template<typename T>
    T& GetComponent(Entity entity);

    /**
     * @brief               Return the component type (ID) of the component
     * @tparam T            Type of the component which wants its ID.
     * @return              The ID of the selected type.
     */
    template<typename T>
    ComponentType GetComponentType()
    {
        std::string componentName = typeid(T).name();
        assert(mComponentsPools.count(componentName));
        return mComponentTypes[componentName];
    }

    // Could be private but public for doing tests
    /**
     * @brief       Return the given pool of component
     * @tparam T    Type of component for the pool
     * @return      Pool of components
     */
    template<typename T>
    std::shared_ptr<ComponentPool<T>> GetComponentPool();

    /**
     * @brief           Noticed all the pools that an entity was destroyed
     * @param entity    The entity which was destroyed
     */
    void EntityDestroyed(Entity entity)
    {
        for (auto const& pair: mComponentsPools) {
            auto const& componentPool = pair.second;
            componentPool->EntityDestroyed(entity);
        }
    }

    //Iterators
    template<typename T>
    typename std::vector<T>::iterator beginIterateComp();

    template<typename T>
    typename std::vector<T>::iterator endIterateComp();
};

template<typename T>
void ComponentManager::RegisterComponent()
{
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName) == 0);
    mComponentsPools.insert({componentName, std::make_shared<ComponentPool<T>>()});
    mComponentTypes.insert({componentName, mNextComponentType});
    mNextComponentType++;
}


template<typename T>
T &ComponentManager::GetComponent(Entity entity)
{
    return GetComponentPool<T>()->Get(entity);
}




template<typename T>
std::shared_ptr<ComponentPool<T>> ComponentManager::GetComponentPool()
{
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName));
    // Cast IComponentPool to ComponentPool<T>
    return std::static_pointer_cast<ComponentPool<T>>(mComponentsPools[componentName]);
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName));
    GetComponentPool<T>()->link(entity, component);
}

template<typename T>
void ComponentManager::DelComponent(Entity entity)
{
    GetComponentPool<T>()->unlink(entity);
}


template<typename T>
typename std::vector<T>::iterator ComponentManager::beginIterateComp()
{
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName));
    std::shared_ptr<ComponentPool<T>> compPool = std::static_pointer_cast<ComponentPool<T>>(mComponentsPools[componentName]);
    return compPool->iterBeginComp();
}

template<typename T>
typename std::vector<T>::iterator ComponentManager::endIterateComp()
{
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName));
    std::shared_ptr<ComponentPool<T>> compPool = std::static_pointer_cast<ComponentPool<T>>(mComponentsPools[componentName]);
    return compPool->iterEndComp();
}

#endif //PEDAROGUE_COMPONENTMANAGER_HPP
