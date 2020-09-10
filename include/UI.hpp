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
    bool to_clear{};

    std::vector<Box*> mToRenderBox;

    std::unordered_map<int, CommandType> mUIBindings;
public:
    UI() = default;
    UI(std::shared_ptr<Window> win);

    // WIN_MSG
    /**
     * @brief               Display a message on the first row
     * @param message       The message to display
     */
    void push_message(Message message);

    // WIN_STATUS
    void render_status_bar(Stats playerStat);

    void newTurn();

    // WIN_INFO
    // Rendering
    void render();
    void clear_last();
    void clear_all();

    UI_List *create_list(std::string &title);
    void destroy_list(UI_List* ui_list);
    void push_list(UI_List* ui_list);

    Box* getLastBox();


};


#endif //PEDAROGUE_UI_HPP
