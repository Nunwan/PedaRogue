//
// Created by nunwan on 04/09/2020.
//

#ifndef PEDAROGUE_INVENTORY_HPP
#define PEDAROGUE_INVENTORY_HPP


#include <core/ECSTypes.hpp>
#include "UI_List.hpp"


class Inventory
{
public:
    Inventory() = default;

    virtual ~Inventory();

    Inventory(Entity& entity, Engine* engine);

    void display();


private:
    Entity mEntity;
    UI_List* mInventory_UI;
    Engine* mEngine;

};


#endif //PEDAROGUE_INVENTORY_HPP
