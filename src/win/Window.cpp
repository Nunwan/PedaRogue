//
// Created by nunwan on 07/06/2020.
//

#include "Window.hpp"

Window::Window() {
    terminal_open();
}

void Window::nextEvent(int eventMask, bool wait)
{
    if (wait) {
        event.key = terminal_read();
    }
}


void Window::print(int x, int y, char* glyph)
{
    terminal_print(x, y, glyph);
}


void Window::clear()
{
    terminal_clear();
}


void Window::refresh()
{
    terminal_refresh();
}


