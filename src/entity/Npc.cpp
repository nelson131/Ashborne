#include "Npc.h"
#include "Entity.h"
#include "EntityHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>

Npc::Npc(){

}

void Npc::spawn(float x, float y, const char *pathToTexture, std::string entityName, Entity::Relationship relationship, bool isVisible, bool isCollisible, bool isAnimated, bool debugMode){
    npc.create(
        x, y,
        pathToTexture,
        entityName,
        relationship,
        isVisible, isCollisible, isAnimated,
        debugMode
    );
}

void Npc::update(){
    npc.update();
    
    /*
    if(npc.inView(eHolder.findEntityById(1))){
        Logger::print(Logger::DEBUG, eHolder.findEntityById(1), " in view of ", npc.getName());
    }
    */
}

void Npc::render(){
    npc.render();
}

void Npc::kill(){
    npc.kill(npc);
}

void Npc::addToInventory(Item& item){
    npc.inventory.add(item);
    npc.updateStats();
}

void Npc::removeFromInventory(Item& item){
    npc.inventory.remove(item);
    npc.updateStats();
}

bool Npc::scanTargets(){
    //scan around logic
    return true;
}