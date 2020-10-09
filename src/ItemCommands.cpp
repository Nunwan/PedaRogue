//
// Created by nunwan on 09/10/2020.
//

#include "ItemCommands.hpp"
#include "Engine.hpp"


void DropItemCommand::execute(Engine *engine)
{
    DropItem dropItem = {name, numberToDelete};
    engine->AddComponent(player, dropItem);
}


DropItemCommand::DropItemCommand(const std::string &name, int numberToDelete, Entity player) : name(name),
                                                                                               numberToDelete(
                                                                                                   numberToDelete),
                                                                                               player(player)
{}
