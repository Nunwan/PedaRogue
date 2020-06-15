//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_INPUTHANDLER_HPP
#define PEDAROGUE_INPUTHANDLER_HPP
#include <memory>
#include <unordered_map>
#include "core/ECSTypes.hpp"
#include "core/ECSManager.hpp"
#include "Window.hpp"
#include "PlayerMovement.hpp"
#include "Components.hpp"

class InputHandler : public System
{
public:
    void Init();
    int process_key(Event event);

private:
    std::shared_ptr<PlayerMovement> mPlayerMovement;

    // Command
    std::unordered_map<int, CommandType> mBindings;


};


#endif //PEDAROGUE_INPUTHANDLER_HPP
