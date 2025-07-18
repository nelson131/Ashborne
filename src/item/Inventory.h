#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "ItemHolder.h"
#include <iostream>
#include <array>
#include <list>

class Inventory {
    public:
    Inventory();

    std::list<Item>& getInventory();
    void add(Item &item);
    void remove(Item &item);

    std::array<int, 7>& getStats();

    private:
    std::array<int, 7> stats;
    std::list<Item> inventory;

    void update();
};

#endif