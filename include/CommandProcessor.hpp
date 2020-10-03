//
// Created by nunwan on 03/10/2020.
//

#ifndef PEDAROGUE_COMMANDPROCESSOR_HPP
#define PEDAROGUE_COMMANDPROCESSOR_HPP


#include <queue>
#include "core/ECSTypes.hpp"


class Command {
public:
    virtual void execute(Engine* engine) = 0;
};

class CommandProcessor : public System
{
private:
    std::queue<Command*> commandQueue;

public:

    void process();

    void pushCommand(Command* command);
};


#endif //PEDAROGUE_COMMANDPROCESSOR_HPP
