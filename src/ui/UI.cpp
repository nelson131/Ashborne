#include "UI.h"
#include "../TextureManager.h"
#include "../entity/EntityHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>

UI::UI(){

}

void UI::init(){
    for(int i = 0; i < this->container.images.size(); i++){
        
    }
}

void UI::update(){

}

void UI::render(){
    if(destRect.w == 0 || destRect.h == 0){

    }

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(eHolder.getRenderer(), &windowWidth, &windowHeight);
    if(locked){
        destRect.x = static_cast<int>(this->position.x);
        //destRect.y = static_cast<int>(windowHeight - this->size.y - this->position.y);
    } else {
        std::cout << "wtf" << std::endl;
    }

}