//
// Created by nunwan on 07/06/2020.
//

#include "Window.hpp"

Window::Window() {
    terminal_open();
    terminal_set("window: size=120x40, title=PedaRogue;");
}

void Window::nextEvent(int eventMask, bool wait)
{
    if (wait) {
        event.key = terminal_read();
    }
}


void Window::print(int x, int y, char* glyph, color_t color)
{
    terminal_color(color);
    terminal_print(x, y, glyph);
    terminal_color(color_from_name("white"));
}


void Window::clear()
{
    terminal_clear();
}


void Window::refresh()
{
    terminal_refresh();
}


