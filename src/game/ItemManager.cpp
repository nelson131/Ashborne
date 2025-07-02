#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <array>
#include "ItemManager.h"

ItemManager itemManager;

ItemManager::ItemManager(){

}

std::list<Item> ItemManager::getInventory(){
    return player_inventory;
}

void ItemManager::addToInventory(Item item){
    player_inventory.push_back(item);
}

void ItemManager::removeFromInventory(Item item){
    player_inventory.remove(item);
}

std::array<int, 6> ItemManager::update_parameters(){
    std::array<int, 6> temp_parameters = {0, 0, 0, 0, 0, 0};
    for(const Item &item : player_inventory){
        for(size_t i = 0; i < temp_parameters.size(); i++){
            temp_parameters[i] = item.parameters[i];
        }
    }
    return temp_parameters;
}

