#include "ItemHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

ItemHolder itemHolder;

ItemHolder::ItemHolder(){

}

void ItemHolder::init(){
    std::ifstream file(path);

    if(!file.is_open()){
        Logger::print(Logger::ERROR, "Failed to find items.ini file");
        return;
    }
    Item result;
    std::string object;
    std::string line;
    bool hasObject = false;
    while(getline(file, line)){
        if(line.empty() || line[0] == '#') continue;
        if(line[0] == '['){
            hasObject = true;
            continue;
        }
        if(hasObject){
            if(line[0] == ';'){
                hasObject = false;
                if(!(result.name == "example")){
                    add(result);
                }
                result = Item{};
            }

            size_t pos = line.find('=');
            if(pos != std::string::npos){
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                if(key == "name"){
                    result.name = value;
                    continue;
                }

                if(key == "desc"){
                    result.desc = value;
                    continue;
                }

                if(key == "parameters"){
                    std::stringstream str(value);
                    char c;
                    int num, idx = 0;
                    while(str >> c){
                        if(std::isdigit(c)){
                            str.putback(c);
                            str >> num;
                            if(idx < result.parameters.size()){
                                result.parameters[idx++] = num;
                            }
                        }
                    }
                }

                if(key == "isEquipable"){
                    result.isEquipable = (value == "true");
                    continue;
                }
            }
        }
    }
    
    Logger::print(Logger::SUCCESS, "Item holder initialized");
}

std::set<Item>& ItemHolder::get() const{
    return itemHolder.holder;
}

const Item& ItemHolder::findBy(const char *name) const{
    for(const Item& item : itemHolder.holder){
        if(item.name == std::string(name)){
            return item;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find item by his name: ", name);
    throw std::runtime_error("Item not found");
}

const Item& ItemHolder::findBy(int id) const{
    for(const Item& item : itemHolder.holder){
        if(item.id == id){
            return item;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find item by his id: ", id);
    throw std::runtime_error("Item not found");
}

void ItemHolder::add(const Item item){
    itemHolder.holder.insert(item);
}

void ItemHolder::remove(const Item &item){
    itemHolder.holder.erase(item);
}

int ItemHolder::getUniqueId(){
    int unique = 0;

    if(itemHolder.holder.empty()){
        return 1;
    }

    for(const Item& item : itemHolder.holder){
        if(item.id > unique){
            unique = item.id;
        }
    }
    return unique + 1;
}