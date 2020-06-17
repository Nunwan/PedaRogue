//
// Created by nunwan on 14/06/2020.
//

#ifndef PEDAROGUE_ENGINE_HPP
#define PEDAROGUE_ENGINE_HPP
#include <memory>
#include "core/ECSManager.hpp"
#include "Components.hpp"
#include "systems/RenderSystem.hpp"
#include "InputHandler.hpp"


class Engine : public ECSManager
{
private:
    std::shared_ptr<Window> mWindow;
    std::shared_ptr<RenderMapSystem> mRenderMapSystem;
    std::shared_ptr<RenderOthersSystem> mRenderOthersSystem;
    std::shared_ptr<InputHandler> mInputHandler;


public:
    const std::shared_ptr<Window> &getMWindow() const;
    Engine();
    void initComponents();
    void initSystems();

    int update();
    void render();

    // Levels activators
    void level_enable(int levelnumber);
    void level_disable(int levelnumber);
};


#endif //PEDAROGUE_ENGINE_HPP
