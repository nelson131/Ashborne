#include "UI.h"
#include "../TextureManager.h"
#include "../entity/EntityHolder.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>

UI::UI(){

}

void UI::init(){

}

void UI::update(){
    for(auto& module : container.modules){
        if(!module){
            Logger::print(Logger::ERROR, "Failed to update UI (", title, ") module");
            continue;
        }
        module->update(position);
    }
}

void UI::render(){
    if(!visible) return;

    for(auto& module : container.modules){
        if(!module){
            Logger::print(Logger::ERROR, "Failed to render UI (", title, ") module");
            continue;
        }
        module->render();
    }
}

ContainerUI& UI::getContainer(){
    return this->container;
}