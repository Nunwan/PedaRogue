//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_INPUTHANDLER_HPP
#define PEDAROGUE_INPUTHANDLER_HPP
#include <memory>
#include <unordered_map>
#include <core/ECSTypes.hpp>
#include <Window.hpp>
#include "systems/PlayerMovement.hpp"

#define DEFAULT_STATE 0
#define UI_STATE 1


class InputHandler : public System
{
public:
    void Init();

    /**
     * @brief           Take an event and create command needed
     * @param event     The event at stakes
     * @return          Return if the game has to quit
     */
    int process_key(EventWin event);

    bool process_key_ui(EventWin event);


private:
    std::shared_ptr<PlayerMovement> mPlayerMovement;

    // Command
    std::unordered_map<int, CommandType> mBindings;
    std::unordered_map<int, CommandType> mUIBindings;


    int mCurrentState;


};


#endif //PEDAROGUE_INPUTHANDLER_HPP
