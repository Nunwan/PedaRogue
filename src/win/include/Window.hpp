//
// Created by nunwan on 07/06/2020.
//

#ifndef PEDAROGUE_WINDOW_HPP
#define PEDAROGUE_WINDOW_HPP
#include <vector>
#include <BearLibTerminal.h>

/* Macro to manipulate principals win. */

#define WIN_JEU 0
#define WIN_INFO 3
#define WIN_MSG 1
#define WIN_STATUS 2

#define HEIGHT_SCREEN 40
#define WIDTH_SCREEN 120
#define NB_WIN 4

#define COL_WHITE 0
#define COL_RED 1
#define COL_BLUE 2
#define COL_CYAN 3
#define COL_MAGENTA 4
#define COL_YELLOW 5

using std::vector;

struct EventWin{
    int key;
};

struct Position {
    int x;
    int y;
};

class Window {
public:
        struct EventWin event;
        Window();
        void nextEvent(int eventMask, bool wait);

        void clear();
        void clear_line(int y, int x_min, int x_max);
        void clear_area(int x, int y, int w, int h);
        void print(int x, int y, char* glyph, color_t color);
        void refresh();

        void select_win(int win);

        color_t color_blue =  color_from_argb(0xff, 0, 0, 0xff);
        color_t color_white = color_from_name("white");
        color_t color_red = color_from_argb(0xff,  0xff, 0, 0);
        color_t color_yellow = color_from_argb(0xff,  0xff, 0xff, 0);

private:
        std::vector<Position> mOffset;
        int mSelectedWin;

};


#endif //PEDAROGUE_WINDOW_HPP
