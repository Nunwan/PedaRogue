//
// Created by nunwan on 02/09/2020.
//

#ifndef PEDAROGUE_UI_HPP
#define PEDAROGUE_UI_HPP


#include "Types.hpp"
#include "Components.hpp"


class UI
{
private:
    std::shared_ptr<Window> mWindow;
public:
    UI() = default;
    UI(std::shared_ptr<Window> win);

    /**
     * @brief               Display a message on the first row
     * @param message       The message to display
     */
    void push_message(Message message);

    void render_status_bar(Stats playerStat);


};


#endif //PEDAROGUE_UI_HPP
