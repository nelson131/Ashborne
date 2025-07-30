#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include "SceneManager.h"
#include "../utils/Logger.h"


void SceneManager::scenesInit(SDL_Renderer *r){
        renderer = r;
        //Test room
        Testroom.name = "Test Room";
        Testroom.id = 0;
        Testroom.layers.clear();

        layer1.init(false);
        layer1.load("assets/floor/grass.png", renderer, 3);
        layer1.setFromCSV(transform(Testroom.name), "layer1");

        layer2.init(true);
        layer2.load("assets/tilemaptest.png", renderer, 2);
        layer2.setFromCSV(transform(Testroom.name), "layer2");
        
        Testroom.layers.push_back(layer1);
        Testroom.layers.push_back(layer2);
        
        Testroom.colliders.insert(&layer2);

        getHolder().insert(&Testroom);
        //
        Logger::print(Logger::SUCCESS, "Scene manager initialized");
};

std::set<Scene*>& SceneManager::getHolder(){
        return sceneManager.holder;
}

const char *SceneManager::transform(const char *name){
        std::string result;
        for(int i = 0; name[i] != '\0'; i++){
                char c = name[i];
                if(c != ' '){
                        result += std::tolower(static_cast<unsigned char>(c));
                }
        }
        return result.c_str();
}