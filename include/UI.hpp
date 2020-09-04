//
// Created by nunwan on 02/09/2020.
//

#ifndef PEDAROGUE_UI_HPP
#define PEDAROGUE_UI_HPP


#include "Types.hpp"
#include "Components.hpp"
#include "UI_List.hpp"


class UI
{
private:
    std::shared_ptr<Window> mWindow;
    std::string currentMessage;
    bool to_clear;

    UI_List mInventory;
    std::vector<Box*> mToRenderBox;

    std::unordered_map<int, CommandType> mUIBindings;
public:
    UI();
    UI(std::shared_ptr<Window> win);

    /**
     * @brief               Display a message on the first row
     * @param message       The message to display
     */
    void push_message(Message message);

    void render_status_bar(Stats playerStat);

    bool process_key(EventWin event);

    void newTurn();

    void render();
    void clear();


};


#endif //PEDAROGUE_UI_HPP
