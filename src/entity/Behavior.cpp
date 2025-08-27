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
    this->entity = e;
    vision.init(entity);
}

Vision& Behavior::getVision(){
    return vision;
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

bool& Behavior::getPathing(){
    return pathing;
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
        pathing = false;
    }

    if(std::abs(dx) < 1.0f && std::abs(dy) < 1.0f){
        entity->position.x = t.getWorldX();
        entity->position.y = t.getWorldY();
        pathingIndex++;
        return;
    }

    if(t.getWorldX() > entity->position.x){
        entity->velocity.x += entity->getAttributes()->getMoveSpeed();
    } else if(t.getWorldX() < entity->position.x){
        entity->velocity.x -= entity->getAttributes()->getMoveSpeed();
    } else {
        entity->velocity.x = 0;
    }

    if(t.getWorldY() > entity->position.y){
        entity->velocity.y += entity->getAttributes()->getMoveSpeed();
    } else if(t.getWorldY() < entity->position.y){
        entity->velocity.y -= entity->getAttributes()->getMoveSpeed();
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