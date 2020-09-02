//
// Created by nunwan on 02/09/2020.
//


#include <memory>
#include <Window.hpp>
#include "UI.hpp"

UI::UI(std::shared_ptr<Window> win)
{
    mWindow = win;
}

void UI::push_message(Message message)
{
    mWindow->select_win(WIN_MSG);
    auto color_message = color_from_argb(0xff, message.r, message.g, message.b);
    mWindow->clear();
    char* cstr = &message.text[0];
    mWindow->print(0, 0, cstr, color_message);
    mWindow->refresh();
}


