#include "Chunk.h"
#include <iostream>

Chunk::Chunk(){

}

void Chunk::load(SDL_Renderer* renderer){
    this->renderer = renderer;
}

void Chunk::update(){

}

void Chunk::render(){
    for(int i = 0; i < layers.size(); i++){
        layers[i].render();
    }
}