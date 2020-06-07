//
// Created by nunwan on 07/06/2020.
//

#ifndef PEDAROGUE_WINDOW_H
#define PEDAROGUE_WINDOW_H
#include <vector>
#include <libtcod.hpp>

/* Macro to manipulate principals win. */

#define WIN_JEU 0
#define WIN_INFO 1
#define WIN_MSG 2
#define WIN_STATUS 3

#define HEIGHT_MAP 30
#define WIDTH_MAP 200
#define NB_WIN 4

#define COL_WHITE 0
#define COL_RED 1
#define COL_BLUE 2
#define COL_CYAN 3
#define COL_MAGENTA 4
#define COL_YELLOW 5

using std::vector;

struct Event {
        TCOD_event_t eventtype;
        TCOD_key_t key;
        TCOD_mouse_t mouse;
};


class Window {
private:

public:
        struct Event event;
        Window();
        void nextEvent(int eventMask, bool wait);

};


#endif //PEDAROGUE_WINDOW_H
