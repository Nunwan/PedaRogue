//
// Created by nunwan on 04/09/2020.
//

#include "Inventory.hpp"
#include "Engine.hpp"


Inventory::Inventory(Entity &entity, Engine *engine, std::string &title)
{
    mEngine = engine;
    mEntity = entity;
    mInventory_UI = mEngine->mUI.create_list(title);
}


Inventory::~Inventory()
{
    mEngine->mUI.destroy_list(mInventory_UI);
}


void Inventory::display()
{
    mEngine->mUI.push_list(mInventory_UI);
}


void Inventory::refresh_list()
{
    // Surety Check but usually not necessary if correctly use
    mInventory_UI->clear_items();
    if (mEngine->HasComponent<Container>(mEntity)) {
        auto& list_items = mEngine->GetComponent<Container>(mEntity);
        for (auto& pair : list_items.contains) {
            mInventory_UI->push_item(new Item(pair.first, pair.second.size(),
                                          new CreateItemMenu(mEntity, pair.first, mInventory_UI->getX(), mInventory_UI->getY())));
        }
    }
}


void OpenInventoryCommand::execute(Engine *engine)
{
    engine->getMInventoryPlayerSystem()->refresh_list();
    engine->getMInventoryPlayerSystem()->display();
}



CreateItemMenu::CreateItemMenu(Entity player,  std::string itemName, int x_parent, int y_parent) : player(player),
                                                                                            itemName(itemName),
                                                                                            x(x_parent +  5),
                                                                                            y(y_parent - 1 )
{
    itemMenu = UI::create_list(x, y, WIDTH_MENU, HEIGHT_MENU, itemName, false);
    itemMenu->push_item(new Item("Drop", -1, new DropItemCommand(itemName, 1, player)));
}


void CreateItemMenu::execute(Engine *engine)
{
    engine->mUI.push_list(itemMenu);
}


void EssaiPourri::execute(Engine *engine)
{
    std::cout<< "essai" << std::endl;

}
