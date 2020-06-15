//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_ENGINE_HPP
#define PEDAROGUE_ENGINE_HPP
#include <memory>
#include "core/ECSManager.hpp"
#include "RenderSystem.hpp"
#include "Components.hpp"


class Engine
{
private:
    std::shared_ptr<RenderMapSystem> mRenderMapSystem;
    std::shared_ptr<RenderOthersSystem> mRenderOthersSystem;
public:
    std::shared_ptr<ECSManager> mECSManager;
    Engine();
    void initComponents();
    void initSystems();

    void render(std::shared_ptr<Window> window);
};


#endif //PEDAROGUE_ENGINE_HPP
