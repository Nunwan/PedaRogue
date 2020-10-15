//
// Created by nunwan on 02/09/2020.
//

#ifndef PEDAROGUE_UI_HPP
#define PEDAROGUE_UI_HPP

#define WIDTH_MENU 20
#define HEIGHT_MENU 10


#include "Types.hpp"
#include "Components.hpp"
#include "UI_List.hpp"
#include "CommandProcessor.hpp"


/**
 * @brief   Class managing all UI related mechanics
 */
class UI
{
private:
    /**
     * Callback pointer to window management
     */
    std::shared_ptr<Window> mWindow;

    /*
     * Message currently at screen on WIN_MSG
     */
    std::string currentMessage;


    /**
     *  If true, message has to be cleaned
     */
    bool to_clear;

    /**
     *  Vector of Box pointers which has to be rendered at screen
     */
    std::vector<Box*> mToRenderBox;

public:
    UI() = default;

    /**
     * @brief           Constructor with window manager given
     * @param win       Window manager
     */
    UI(std::shared_ptr<Window> win);

    // WIN_MSG
    /**
     * @brief               Display a message on the first row
     * @param message       The message to display
     */
    void push_message(Message message);

    // WIN_STATUS
    /**
     * @brief                   Render the status bar of the player
     * @param playerStat        Stats of the player to be rendered
     */
    void render_status_bar(Stats playerStat);

    /**
     * @brief       Indicating that it is a new turn and do actions of end turn
     */
    void newTurn();

    // WIN_INFO
    // Rendering
    /**
     * @brief   WIN_INFO rendering function
     */
    void render();

    /**
     * @brief Clear the last box at screen
     */
    void clear_last();

    /**
     * @brief clear all the WIN_INFO screen
     */
    void clear_all();

    /**
     * @brief           Return a new allcoated UI_List with given title
     * @param title     The title of the List
     * @return          Pointer to this new list
     */
    static UI_List *create_list(std::string &title, bool permanent = true);
    static UI_List *create_list(int x , int y, int w, int h, std::string &title, bool permanent = true);

    /**
     * @brief               Free and destroy the list
     * @param ui_list       the list to destroy
     */
    void destroy_list(UI_List* ui_list);


    /**
     * @brief               Push a list to the vector of rendering
     * @param ui_list       The list to render
     */
    void push_list(UI_List* ui_list);

    /**
     * @brief       Give the last Box which is rendered at screen
     * @return      A pointer to the last box rendered at screen
     */
    Box* getLastBox();

    bool isEmpty();
};


class UISelectUpCommand : public Command
{
    void execute(Engine *engine) override;
};

class UISelectDownCommand : public Command
{
    void execute(Engine *engine) override;
};

class UISelectedCommand : public Command
{
    void execute(Engine *engine) override;
};



#endif //PEDAROGUE_UI_HPP
