//
// Created by nunwan on 02/09/2020.
//

#ifndef PEDAROGUE_UI_HPP
#define PEDAROGUE_UI_HPP


#include "Types.hpp"


class UI
{
private:
    std::shared_ptr<Window> mWindow;
public:
    UI() = default;
    UI(std::shared_ptr<Window> win);
    void push_message(Message message);

};


#endif //PEDAROGUE_UI_HPP
