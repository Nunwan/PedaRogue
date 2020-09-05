//
// Created by nunwan on 03/09/2020.
//


#include "UI_List.hpp"
#include "Window.hpp"


Box::Box()
{
    h = HEIGHT_SCREEN - 1;
    w = 1 * WIDTH_SCREEN / 3 - 1;
    y = 0;
    x = 0;
}


Box::Box(int width, int height, int x_begin, int y_begin)
{
    w = width;
    h = height;
    x = x_begin;
    y = y_begin;
}


void Box::render(std::shared_ptr<Window> window)
{
    window->select_win(WIN_INFO);
    for (int x_it = x; x_it < x + w - 1; ++x_it) {
        window->print(x_it, y, "-", window->color_white);
        window->print(x_it, y + h - 1, "-", window->color_white);
    }
    for (int y_it = y; y_it < y + h - 1; ++y_it) {
        window->print(x, y_it, "|", window->color_white);
        window->print(x + w - 1, y_it, "|", window->color_white);
    }
}


void UI_List::render(std::shared_ptr<Window> window)
{
    Box::render(window);

}
