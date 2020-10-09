//
// Created by nunwan on 09/10/2020.
//

#ifndef PEDAROGUE_ITEMCOMMANDS_HPP
#define PEDAROGUE_ITEMCOMMANDS_HPP

#include "CommandProcessor.hpp"
#include "Components.hpp"

class DropItemCommand : public Command {
private:
    std::string name;
    int numberToDelete;
    Entity player;

public:
    DropItemCommand(const std::string &name, int numberToDelete, Entity player);

    void execute(Engine *engine) override;
};

#endif //PEDAROGUE_ITEMCOMMANDS_HPP
