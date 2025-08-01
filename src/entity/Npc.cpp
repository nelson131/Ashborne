#include "Npc.h"
#include "Entity.h"
#include "EntityHolder.h"
#include "../utils/Logger.h"
#include "../alg/Vector.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <list>

Npc::Npc(){

}

void Npc::spawn(float x, float y, int& w, int& h, const char *pathToTexture, std::string entityName, bool isVisible, bool isCollisible, bool isAnimated, bool debugMode){
    npc.create(
        x, y,
        w, h,
        pathToTexture,
        entityName,
        isVisible, isCollisible, isAnimated,
        debugMode
    );
    behavior.init(&npc);

    behavior.setPathing(true);
    behavior.addDot(Tile(4, 2, 64));
    behavior.addDot(Tile(0, 2, 64));
    behavior.addDot(Tile(2, 2, 64));
    
    behavior.setVisionRadius(200);
}

void Npc::update(){
    behavior.updateVision();
    behavior.updatePathing();
    npc.update();
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