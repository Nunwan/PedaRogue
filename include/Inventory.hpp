//
// Created by nunwan on 04/09/2020.
//

#ifndef PEDAROGUE_INVENTORY_HPP
#define PEDAROGUE_INVENTORY_HPP


#include <core/ECSTypes.hpp>
#include <unordered_map>
#include "UI_List.hpp"


class Inventory
{
public:
    Inventory() = default;

    virtual ~Inventory();

    Inventory(Entity &entity, Engine *engine, std::string &title);

    void display();

    void refresh_list();

    void select_next();

    void select_previous();

private:
    Entity mEntity;
    UI_List* mInventory_UI;
    Engine* mEngine;

    std::unordered_map<std::string, int> mItems;

};


#endif //PEDAROGUE_INVENTORY_HPP
