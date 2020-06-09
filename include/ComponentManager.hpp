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
public:
    ComponentManager();

    template<typename T>
    void RegisterComponent();

    template<typename T>
    T& GetComponent(Entity entity);
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
    std::string componentName = typeid(T).name();
    assert(mComponentsPools.count(componentName));
    ComponentPool<T> componentPool = mComponentsPools[componentName];
    return componentPool.Get(entity);
}

#endif //PEDAROGUE_COMPONENTMANAGER_HPP
