#include "Vision.h"
#include "EntityHolder.h"
#include "../utils/Logger.h"
#include <iostream>

Vision::Vision(){

}

void Vision::init(Entity*& e){
    this->self = e;
}

void Vision::update(){
    for(const auto& [id, e] : eHolder.get()){
        if(!e || e == self) continue;
        if(self->position.getDistance(e->position) <= range){
            if(contains(e)) continue;
            add(e);
        } else if(contains(e)){
            remove(e);
        }
    }
}

float Vision::getRange(){
    return range / SCALE;
}

float& Vision::getRangeReal(){
    return range;
}

void Vision::setRange(float r){
    range = r * SCALE;
}

void Vision::add(Entity* e){
    inRange.push_back(e);
}

void Vision::remove(Entity* e){
    for(size_t i = 0; i < inRange.size(); i++){
        if(inRange[i] == e){
            inRange.erase(inRange.begin() + i);
            i--;
        }
    }
}

bool Vision::contains(Entity* e){
    for(size_t i = 0; i < inRange.size(); i++){
        if(inRange[i] == e) return true;
    }
    return false;
}

std::vector<Entity*>& Vision::getInRange(){
    return inRange;
}