#include "EntityHolder.h"
#include <iostream>

EntityHolder eHolder;

EntityHolder::EntityHolder(){
    eHolder.sdlRenderer = nullptr;
}

std::unordered_map<int, Entity*>& EntityHolder::get(){
    return eHolder.holder;
}

Entity* EntityHolder::findEntityById(int id){
    if(eHolder.get().count(id)){
        return eHolder.get()[id];
    }
    Logger::print(Logger::ERROR, "Failed to find entity by id");
    return nullptr;
}

int EntityHolder::getIdBy(const Entity* e) const{
    for(const auto& [id, entity] : eHolder.holder){
        if(entity == e){
            return id;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find id by entity");
    return -1;
}

std::string EntityHolder::getNameBy(const Entity* e) const{
    for(const auto& [id, entity] : eHolder.holder){
        if(entity && entity->getName() == e->getName()){
            return entity->getName();
        }
    }
    Logger::print(Logger::ERROR, "Failed to find name by entity");
    return "ERROR";
}

void EntityHolder::add(Entity* e){
    eHolder.get()[e->getId()] = e;
}

void EntityHolder::remove(Entity* e){
    int id = getIdBy(e);
    if(id == -1){
        Logger::print(Logger::ERROR, "Failed to ыfind entity in remove func");
        return;
    }
    eHolder.get().erase(id);
}

int EntityHolder::getUniqueId(){
    int uniqueId = 0;

    if(eHolder.holder.empty()){
        return 1;
    }

    for(const auto& [id, Entity] : eHolder.get()){
        if(id > uniqueId){
            uniqueId = id;
        }
    }
    return uniqueId + 1;
}

SDL_Renderer* EntityHolder::getRenderer(){
    return eHolder.sdlRenderer;   
}

void EntityHolder::init(SDL_Renderer *renderer){
    eHolder.sdlRenderer = renderer;
    Logger::print(Logger::SUCCESS, "Entity holder initialized");
}

bool EntityHolder::inRange(const Entity* e1, const Entity* e2){
    return e1->position.getDistance(e2->position) <= avr;
}