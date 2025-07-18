#include "ItemHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <set>

ItemHolder itemHolder;

ItemHolder::ItemHolder(){

}

void ItemHolder::init(){
    const Item sword {
        "Sword",
        getUniqueId(),
        {0, 0, 0, 10, 0, 0, 0}
    };
    add(&sword);
}

std::set<const Item*>& ItemHolder::get() const{
    return itemHolder.holder;
}

const Item* ItemHolder::findBy(const char *name) const{
    for(const Item* item : itemHolder.holder){
        if(item->name == name){
            return item;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find item by his name: ", name);
}

const Item* ItemHolder::findBy(int id) const{
    for(const Item* item : itemHolder.holder){
        if(item->id == id){
            return item;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find item by his id: ", id);
}

void ItemHolder::add(const Item *item){
    itemHolder.holder.insert(item);
}

void ItemHolder::remove(const Item *item){
    itemHolder.holder.erase(item);
}

int ItemHolder::getUniqueId(){
    int unique = 0;

    if(itemHolder.holder.empty()){
        return 1;
    }

    for(const Item *item : itemHolder.holder){
        if(item->id > unique){
            unique = item->id;
        }
    }
    return unique + 1;
}