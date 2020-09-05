//
// Created by nunwan on 04/09/2020.
//

#include "Inventory.hpp"
#include "Engine.hpp"


Inventory::Inventory(Entity &entity, Engine* engine)
{
    mEngine = engine;
    mEntity = entity;
    mInventory_UI = mEngine->mUI.create_list();
}


Inventory::~Inventory()
{
    mEngine->mUI.destroy_list(mInventory_UI);
}


void Inventory::display()
{
    mEngine->mUI.push_list(mInventory_UI);

}


