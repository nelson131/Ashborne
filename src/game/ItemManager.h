#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <iostream>
#include <array>
#include <list>

struct Item
{
    const char *name;
    int item_id;
    std::array<int, 6> parameters;
    /*
    1. HP
    2. Mana
    3. Phys damage
    4. Magic damage
    5. Phys res
    6. Magic res
    */

    bool operator==(const Item& other) const {
        return parameters == other.parameters;
    }
};

class ItemManager {
    public:
    ItemManager();
    
    std::list<Item> getInventory();
    void addToInventory(Item item);
    void removeFromInventory(Item item);

    std::array<int, 6> update_parameters();

    private:
    std::list<Item> player_inventory;
};

extern ItemManager itemManager;

#endif