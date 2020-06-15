//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_ENGINE_HPP
#define PEDAROGUE_ENGINE_HPP
#include <memory>
#include "core/ECSManager.hpp"
#include "RenderSystem.hpp"
#include "Components.hpp"
#include "InputHandler.hpp"


class Engine
{
private:
    std::shared_ptr<Window> mWindow;
    std::shared_ptr<RenderMapSystem> mRenderMapSystem;
    std::shared_ptr<RenderOthersSystem> mRenderOthersSystem;
    std::shared_ptr<InputHandler> mInputHandler;
public:
    std::shared_ptr<ECSManager> mECSManager;
    Engine();
    void initComponents();
    void initSystems();

    int update();
    void render();
};


#endif //PEDAROGUE_ENGINE_HPP
