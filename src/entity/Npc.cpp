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

void Npc::spawn(){
    npc.create(
        spawnX, spawnY,
        width, height,
        path.c_str(),
        name,
        animated,
        debugmode
    );

    behavior.init(&npc);
    npc.velocity = {0, 0};
}

void Npc::update(){
    behavior.getVision().update();

    if(behavior.getPathing()){
        behavior.updatePathing();
    }
    
    npc.update();
}

void Npc::render(){
    npc.render();
}

void Npc::kill(){
    npc.kill(npc);
}

void Npc::setSpawnPars(float& x, float& y, int& w, int& h, std::string p, std::string& n, bool& anim, bool& debug){
    spawnX = x;
    spawnY = y;
    width = w;
    height = h;
    path = p;
    name = n;
    animated = anim;
    debugmode = debug;
}

Entity& Npc::getEntity(){
    return npc;
}

Behavior& Npc::getBehavior(){
    return behavior;
}

void Npc::setBehavior(bool p, float visionRadius){
    behavior.setPathing(p);
    behavior.getVision().setRange(visionRadius);
}

void Npc::addDots(std::vector<Vector> d){
    for(int i = 0; i < d.size(); i++){
        behavior.addDot(Tile(d[i].x, d[i].y, width * SCALE));
    }
}

void Npc::addToInventory(Item& item){
    npc.getInventory()->add(item);
    npc.getAttributes()->updateStats();
}

void Npc::removeFromInventory(Item& item){
    npc.getInventory()->remove(item);
    npc.getAttributes()->updateStats();
}