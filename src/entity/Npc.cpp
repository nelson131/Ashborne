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
    if(pathing){
        if(index >= dots.size()){
            npc.velocity = {0, 0};
            return;
        }
        npc.velocity = {0, 0};
        Tile t = dots[index];
        float dx = t.getWorldX() - npc.position.x;
        float dy = t.getWorldY() - npc.position.y;
        float distance = npc.position.getDistance(dx, dy);

        if(dx < 1.0f && dy < 1.0f){
            npc.position.x = t.getWorldX();
            npc.position.y = t.getWorldY();
            index++;
            return;
        }

        if(t.getWorldX() > npc.position.x){
            npc.velocity.x += npc.getMS();
        } else if(t.getWorldX() < npc.position.x){
            npc.velocity.x -= npc.getMS();
        } else {
            npc.velocity.x = 0;
        }

        if(t.getWorldY() > npc.position.y){
            npc.velocity.y += npc.getMS();
        } else if(t.getWorldY() < npc.position.y){
            npc.velocity.y -= npc.getMS();
        } else {
            npc.velocity.y = 0;
        }
    }
    Logger::print(Logger::DEBUG, "Current dot: ", index);
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

bool Npc::scanTargets(){
    //scan around logic
    return false;
}

std::vector<Tile>& Npc::getDots(){
    return dots;
}

void Npc::addDot(Tile t){
    dots.push_back(t);
}

void Npc::removeDot(Tile t){
    if(dots.empty()){
        Logger::print(Logger::ERROR, "Dots (", npc.getName(), ") are empty");
        return;
    }
    int index = 0;
    for(int i = 0; i < dots.size(); i++){
        if(dots[i] == t){
            index = i;
        }
    }
    dots.erase(dots.begin() + index);
}

void Npc::setPathing(bool b){
    pathing = b;
}

bool& Npc::getPathing(){
    return pathing;
}