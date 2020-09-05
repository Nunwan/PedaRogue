//
// Created by nunwan on 15/06/2020.
//

#ifndef PEDAROGUE_TYPES_HPP
#define PEDAROGUE_TYPES_HPP
#include <string>

enum CommandType {
    UpPlayer,
    DownPlayer,
    RightPlayer,
    LeftPlayer,
    NextLevelPlayer,
    PreviousLevelPlayer,
    UICommand,
    OpenInventoryPlayer,
    UpMenu,
    DownMenu

};


struct Message {
    std::string text;
    int r, g, b;
};


#endif //PEDAROGUE_TYPES_HPP
