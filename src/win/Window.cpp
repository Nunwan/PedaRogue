//
// Created by nunwan on 07/06/2020.
//

#include "Window.hpp"

Window::Window() {
    TCODConsole::initRoot(WIDTH_MAP, HEIGHT_MAP, "PedaRogue");
    TCODConsole::setCustomFont("data/fonts/dejavu_wide16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD, 32, 8);
    TCODConsole::root->setDefaultBackground(TCODColor::black);
    TCODConsole::root->setDefaultForeground(TCODColor::white);
    TCODConsole::root->setChar(10, 10, '@');
    TCODConsole::flush();
}

void Window::nextEvent(int eventMask, bool wait)
{
    if (wait) {
        event.eventtype = TCODSystem::waitForEvent(eventMask, &event.key, &event.mouse, true);
        return;
    }
    event.eventtype = TCODSystem::checkForEvent(eventMask, &event.key, &event.mouse);
}


