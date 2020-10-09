//
// Created by nunwan on 04/09/2020.
//

#ifndef PEDAROGUE_INVENTORY_HPP
#define PEDAROGUE_INVENTORY_HPP


#include <core/ECSTypes.hpp>
#include <unordered_map>
#include "UI_List.hpp"
#include "CommandProcessor.hpp"
#include "ItemCommands.hpp"


/**
 * Class that manage an Inventory
 */
class Inventory
{
public:
    Inventory() = default;

    virtual ~Inventory();

    /**
     * @brief               Constructor for a given entity which has inventory and has to manage it
     * @param entity        The entity to retrieve inventory
     * @param engine        Callback pointer to engine
     * @param title         Title of the inventory
     */
    Inventory(Entity &entity, Engine *engine, std::string &title);

    /**
     * @brief               Display the inventory on WIN_INFO
     */
    void display();

    /**
     * @brief               Refresh the inventory when ask
     */
    void refresh_list();


private:
    /**
     * Entity linked to the inventory
     */
    Entity mEntity;

    /**
     * The list representing Inventory on screen
     */
    UI_List* mInventory_UI;

    /**
     * Callback pointer to engine
     */
    Engine* mEngine;

    /**
     * Items composing the inventory
     */
    std::unordered_map<std::string, int> mItems;
};

class OpenInventoryCommand : public Command
{
public:
    void execute(Engine *engine) override;

};

class CreateItemMenu : public Command
{
private:
    Entity player;
    std::string itemName;
    UI_List* itemMenu;
    int x, y;
public:
    CreateItemMenu(Entity player,  std::string itemName, int x_parent, int y_parent);
    void execute(Engine *engine) override;
};

class EssaiPourri : public Command
{
public:
    void execute(Engine *engine) override;
};

#endif //PEDAROGUE_INVENTORY_HPP
