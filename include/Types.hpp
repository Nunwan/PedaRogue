//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_TYPES_HPP
#define PEDAROGUE_TYPES_HPP
#include <string>

enum DirectionMove {
    UpPlayer,
    DownPlayer,
    RightPlayer,
    LeftPlayer,
    NextLevelPlayer,
    PreviousLevelPlayer,
};



struct Message {
    std::string text;
    int r, g, b;
};

struct Color {
    int r, g, b;
};

#endif //PEDAROGUE_TYPES_HPP
