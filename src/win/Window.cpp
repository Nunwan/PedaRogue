//
// Created by nunwan on 07/06/2020.
//

#include "Window.hpp"

Window::Window() {
    TCODConsole::initRoot(WIDTH_MAP, HEIGHT_MAP, "PedaRogue", false);
    TCODConsole::setCustomFont("data/fonts/dejavu_wide16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD, 32, 8);
    TCODConsole::root->setDefaultBackground(TCODColor::grey);
    TCODConsole::root->setDefaultForeground(TCODColor::white);
    event.eventtype = TCOD_EVENT_ANY;
}

void Window::nextEvent(int eventMask, bool wait)
{
    if (wait) {
        event.eventtype = TCODSystem::waitForEvent(eventMask, &event.key, &event.mouse, true);
        return;
    }
    event.eventtype = TCODSystem::checkForEvent(eventMask, &event.key, &event.mouse);
}


void Window::print(int x, int y, int glyph, TCODColor color)
{
    TCODConsole::root->setCharForeground(x, y, color);
    TCODConsole::root->setChar(x, y, glyph);
    printf("%i , %i, %c, %i, %i, %i \n", x, y, glyph, color.b, color.r, color.g);
}


void Window::clear()
{
    TCODConsole::root->clear();
}


void Window::refresh()
{
    TCODConsole::flush();
}


