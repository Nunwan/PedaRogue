//
// Created by nunwan on 07/06/2020.
//

#include "Window.hpp"

Window::Window() {
    terminal_open();
    terminal_set("window: size=120x40, title=PedaRogue;");

    mOffset.push_back({0, 1});
    mOffset.push_back({0, 0});
    mOffset.push_back({0, 4 * HEIGHT_SCREEN/5 + 1});
    mOffset.push_back({2 * WIDTH_SCREEN / 3 + 1, 1});

    mSelectedWin = 0;
}

void Window::nextEvent(int eventMask, bool wait)
{
    if (wait) {
        event.key = terminal_read();
    }
}


void Window::print(int x, int y, char* glyph, color_t color)
{
    int x_offset = mOffset[mSelectedWin].x;
    int y_offset = mOffset[mSelectedWin].y;
    terminal_color(color);
    terminal_print(x + x_offset, y + y_offset, glyph);
    terminal_color(color_from_name("white"));
}


void Window::clear()
{
    terminal_clear_area(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);
}


void Window::refresh()
{
    terminal_refresh();
}


void Window::select_win(int win)
{
    mSelectedWin = win;
    terminal_layer(win);
}


void Window::clear_line(int y, int x_min, int x_max)
{
    int y_offset = mOffset[mSelectedWin].y;
    terminal_clear_area(x_min, y + y_offset, x_max - x_min, 1);
}


void Window::clear_area(int x, int y, int w, int h)
{
    int y_offset = mOffset[mSelectedWin].y;
    int x_offset = mOffset[mSelectedWin].x;
    terminal_clear_area(x + x_offset, y + y_offset,  w, h);

}


