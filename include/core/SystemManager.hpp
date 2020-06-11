//
// Created by nunwan on 10/06/2020.
//

#ifndef PEDAROGUE_SYSTEMMANAGER_HPP
#define PEDAROGUE_SYSTEMMANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>
#include "ECSTypes.hpp"


class SystemManager {
private:
    std::unordered_map<std::string, std::shared_ptr<System>> mSystems;
    std::unordered_map<std::string, Signature> mSysSignature;
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSignature(Signature signature);


    template<typename T>
    Signature GetSignature();

    void EntityDestroyed(Entity entity)
    {
        for (auto const& pair : mSystems) {
            auto const& system = pair.second;
            system->getEntities().erase(entity);
        }

    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for (auto const& pair : mSystems) {
            auto const& systemName = pair.first;
            auto const& system = pair.second;

            auto const& systemSignature = mSysSignature[systemName];

            if ((systemSignature & entitySignature) == systemSignature) {
                system->getEntities().insert(entity);
            }
            else {
                system->getEntities().erase(entity);
            }
        }

    }

};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
    std::string systemName = typeid(T).name();
    assert(mSystems.count(systemName) == 0);
    auto system = std::make_shared<T>();
    mSystems.insert({systemName, system});
    Signature sysSignature;
    SetSignature<T>(sysSignature);
    return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
    std::string systemName = typeid(T).name();
    assert(mSystems.count(systemName));
    if (mSysSignature.count(systemName) != 0) {
        mSysSignature[systemName] = signature;
        return;
    }
    mSysSignature.insert({systemName, signature});
}


template<typename T>
Signature SystemManager::GetSignature()
{
    std::string systemName = typeid(T).name();
    assert(mSystems.count(systemName));
    if (mSysSignature.count(systemName)) {
        return mSysSignature[systemName];
    }
}


#endif //PEDAROGUE_SYSTEMMANAGER_HPP
