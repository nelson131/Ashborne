#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <array>
#include "ItemManager.h"

ItemManager itemManager;

ItemManager::ItemManager(){

}

std::list<Item> ItemManager::getInventory(){
    return playerInventory;
}

void ItemManager::addToInventory(Item item){
    playerInventory.push_back(item);
}

void ItemManager::removeFromInventory(Item item){
    playerInventory.remove(item);
}

std::array<int, 6> ItemManager::updateParameters(){
    std::array<int, 6> tempParameters = {0, 0, 0, 0, 0, 0};
    for(const Item &item : playerInventory){
        for(size_t i = 0; i < tempParameters.size(); i++){
            tempParameters[i] = item.parameters[i];
        }
    }
    return tempParameters;
}

