#include "UI.h"
#include "../TextureManager.h"
#include "../entity/EntityHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>

UI::UI(){

}

void UI::init(){
    this->texture = TextureManager::load(texturePath.c_str(), eHolder.getRenderer());
    if(!texture){
        Logger::print(Logger::ERROR, "Failed to load texture in the UI init");
    }
}

void UI::update(){

}

void UI::render(){
    if(destRect.w == 0 || destRect.h == 0){
        destRect.w = static_cast<int>(this->size.x);
        destRect.h = static_cast<int>(this->size.y);
    }

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(eHolder.getRenderer(), &windowWidth, &windowHeight);
    if(locked){
        destRect.x = static_cast<int>(this->position.x);
        destRect.y = static_cast<int>(windowHeight - this->size.y - this->position.y);
    } else {
        std::cout << "wtf" << std::endl;
    }

    SDL_RenderCopy(eHolder.getRenderer(), texture, nullptr, &destRect);
}