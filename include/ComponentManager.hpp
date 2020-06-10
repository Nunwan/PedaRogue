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



class ComponentManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<IComponentPool>> mComponentsPools;
    std::unordered_map<std::string, ComponentType> mComponentTypes;
    ComponentType mNextComponentType;

    template<typename T>
    std::shared_ptr<ComponentPool<T>> GetComponentPool();
public:
    ComponentManager();

    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity entity,T component);

    template<typename T>
    void DelComponent(Entity entity);

    template<typename T>
    T& GetComponent(Entity entity);

    void EntityDestroyed(Entity entity);
};

template<typename T>
void ComponentManager::RegisterComponent()
{
    std::string componentName = typeid(T).name();
    if (!mComponentsPools.count(componentName)) {
        mComponentsPools.insert({componentName, std::make_shared<ComponentPool<T>()>()});
        mComponentTypes.insert({componentName, mNextComponentType});
        mNextComponentType++;
    }
}

ComponentManager::ComponentManager()
{
    mNextComponentType = 0;
}

template<typename T>
T &ComponentManager::GetComponent(Entity entity)
{
    return GetComponentPool<T>().Get(entity);
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
    GetComponentPool<T>().unlink(entity);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
    for (auto const& pair: mComponentsPools) {
        auto const& componentPool = pair.second;
        componentPool->EntityDestroyed(entity);
    }

}

#endif //PEDAROGUE_COMPONENTMANAGER_HPP
