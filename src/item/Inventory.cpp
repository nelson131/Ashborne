#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <array>
#include "Inventory.h"

Inventory::Inventory(){

}

void Inventory::update(){
    for(const Item &item : inventory){
        for(size_t i = 0; i < stats.size(); i++){
            stats[i] += item.parameters[i];
        }
    }
}

const std::list<Item>& Inventory::getInventory(){
    return inventory;
}

void Inventory::add(Item &item){
    inventory.push_back(item);
    update();
}

void Inventory::remove(Item &item){
    inventory.remove(item);
    update();
}

const std::array<int, 7>& Inventory::getStats(){
    return stats;
}