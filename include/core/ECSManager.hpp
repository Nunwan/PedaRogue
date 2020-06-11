//
// Created by nunwan on 11/06/2020.
//

#ifndef PEDAROGUE_ECSMANAGER_HPP
#define PEDAROGUE_ECSMANAGER_HPP
#include <memory>
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "EntityManager.hpp"


class ECSManager {
private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;
public:
    ECSManager()
    {
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }


    // Entity Management
    Entity CreateEntity()
    {
        return mEntityManager->CreateEntity();
    }


    void DestroyEntity(Entity entity)
    {
        mEntityManager->DestroyEntity(entity);
        mComponentManager->EntityDestroyed(entity);
        mSystemManager->EntityDestroyed(entity);
    }


    // Component Management
    template<typename T>
    void RegisterComponent()
    {
        mComponentManager->RegisterComponent<T>();
    }


    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        mComponentManager->AddComponent(entity, component);
        auto entitySignature = mEntityManager->getSignature(entity);
        entitySignature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity, entitySignature);
        mSystemManager->EntitySignatureChanged(entity, entitySignature);

    }


    template<typename T>
    void DelComponent(Entity entity)
    {
        mComponentManager->DelComponent<T>(entity);

        auto entitySignature = mEntityManager->getSignature(entity);
        entitySignature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->SetSignature(entity, entitySignature);
        mSystemManager->EntitySignatureChanged(entity, entitySignature);
    }


    template<typename T>
    T& GetComponent(Entity entity)
    {
        return mComponentManager->GetComponent<T>(entity);
    }


    template<typename T>
    typename std::vector<T>::iterator BeginComp()
    {
        return mComponentManager->beginIterateComp<T>();
    }


    template<typename T>
    typename std::vector<T>::iterator EndComp()
    {
        return mComponentManager->endIterateComp<T>();
    }


    // System Management
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return mSystemManager->RegisterSystem<T>();
    }


    template<typename T>
    void SetSystemSignature(Signature signature)
    {
        mSystemManager->SetSignature<T>(signature);
    }


    template<typename Tsys, typename Tcomp>
    void UseComponent()
    {
        Signature sysSignature = mSystemManager->GetSignature<Tsys>();
        sysSignature.set(mComponentManager->GetComponentType<Tcomp>(), true);
        mSystemManager->SetSignature<Tsys>(sysSignature);
    }
};
#endif //PEDAROGUE_ECSMANAGER_HPP
