#include "Behavior.h"
#include "EntityHolder.h"
#include "../alg/Vector.h"
#include "../utils/Tile.h"
#include "../utils/Logger.h"
#include "../utils/Config.h"
#include <iostream>

Behavior::Behavior(){

}

void Behavior::init(Entity* e){
    entity = e;
}

Behavior::Relationship& Behavior::getRelationship(){
    return rel;
}

void Behavior::setRelationship(Relationship r){
    rel = r;
}

void Behavior::setPathing(bool b){
    pathing = b;
}

void Behavior::updatePathing(){
    if(!pathing){
        Logger::print(Logger::ERROR, "Failed to update pathing cause pathing were disabled");
        return;
    }

    if(pathingIndex >= dots.size()){
        entity->velocity = {0, 0};
        return;
    }

    entity->velocity = {0, 0};
    Tile t = dots[pathingIndex];
    float dx = t.getWorldX() - entity->position.x;
    float dy = t.getWorldY() - entity->position.y;

    if(t.isBlocked()){
        pathing - false;
    }

    if(std::abs(dx) < 1.0f && std::abs(dy) < 1.0f){
        entity->position.x = t.getWorldX();
        entity->position.y = t.getWorldY();
        pathingIndex++;
        return;
    }

    if(t.getWorldX() > entity->position.x){
        entity->velocity.x += entity->getMoveSpeed();
    } else if(t.getWorldX() < entity->position.x){
        entity->velocity.x -= entity->getMoveSpeed();
    } else {
        entity->velocity.x = 0;
    }

    if(t.getWorldY() > entity->position.y){
        entity->velocity.y += entity->getMoveSpeed();
    } else if(t.getWorldY() < entity->position.y){
        entity->velocity.y -= entity->getMoveSpeed();
    } else {
        entity->velocity.y = 0;
    }
}

void Behavior::addDot(Tile t){
    dots.push_back(t);
}

void Behavior::removeDot(Tile t){
    if(dots.empty()){
        Logger::print(Logger::ERROR, "Dotsa are empty");
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

std::vector<Tile>& Behavior::getDots(){
    return dots;
}

void Behavior::setVisionRadius(float f){
    visionRadius = f * SCALE;
}

float Behavior::getVisionRadius(){
    return visionRadius / SCALE;
}

float& Behavior::getVisionRadiusReal(){
    return visionRadius;
}

void Behavior::updateVision(){
    for(const auto& [id, e] : eHolder.get()){
        if(!e || e == entity) continue;
        if(entity->position.getDistance(e->position) <= visionRadius){
            if(contains(e)) continue;
            inRadius.push_back(e);
        } else if(contains(e)){
            removeFromRadius(e);
        }
    }
}

void Behavior::addToRadius(Entity* e){
    inRadius.push_back(e);
}

void Behavior::removeFromRadius(Entity* e){
    for(size_t i = 0; i < inRadius.size(); i++){
        if(inRadius[i] == e){
            inRadius.erase(inRadius.begin() + i);
            i--;
        }
    }
}

bool Behavior::contains(Entity* e){
    for(size_t i = 0; i < inRadius.size(); i++){
        if(inRadius[i] == e) return true;
    }
    return false;
}

std::vector<Entity*>& Behavior::getInRadius(){
    return inRadius;
}