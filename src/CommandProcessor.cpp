//
// Created by nunwan on 03/10/2020.
//


#include "CommandProcessor.hpp"
#include "Engine.hpp"


void CommandProcessor::process()
{
    Command* command;
    while (!commandQueue.empty()) {
        command = commandQueue.front();
        command->execute(mEngine);
        commandQueue.pop();
    }
}


void CommandProcessor::pushCommand(Command *command)
{
    if (command != nullptr) {
        commandQueue.push(command);
    }
}


