#include "UIManager.h"
#include "UI.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <memory>

UIManager uiManager;

UIManager::UIManager(){

}

void UIManager::init(InitType type, const char* title){
    std::string path = "resources/ui/";
    switch (type) {
        case InitType::PLAYER:
            path += "player.ini";
            break;
        case InitType::WORLD:
            path += "world.ini";
            break;
        default:
            break;
    }

    std::ifstream file(path.c_str());
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "Failed to open ui.ini file");
        return;
    }

    UI result = {};
    std::string objectTitle = "";

    UIModule::Image img = {};

    std::string line;
    bool hasObject = false;
    bool hasModule = false;
    while(getline(file, line)){
        if(line[0] == '#' || line.empty()) continue;
        if(line[0] == '['){
            objectTitle = line;
            objectTitle.erase(0, 1);
            objectTitle.erase(objectTitle.size() - 1);
            
            if(title != nullptr){
                hasObject = (objectTitle == title);
            }
            else hasObject = true;
        }
        if(line[0] == '>'){
            hasModule = true;

            std::string moduleTitle = line;
            moduleTitle.erase(0, 1);
            moduleTitle.erase(0, 1);
            moduleTitle.erase(objectTitle.size() - 1);
        }
        if(hasObject){
            if(line[1] == ';' && hasModule){
                result.container.images.push_back(img);
                continue;
            }
            if(line[0] == ';'){
                if(!hasModule){
                    std::vector<UI>* pointStash = nullptr;
                    switch(type){
                        case InitType::PLAYER:
                            pointStash = &uiManager.stash.player;
                            break;
                        case InitType::WORLD:
                            pointStash = &uiManager.stash.world;
                            break;
                        default:
                            break;
                    }
                    result.init();
                    pointStash->push_back(result);

                    result= {};
                    hasObject = false;
                    if(title != nullptr){
                        return;
                    }
                } else {
                    hasModule = false;
                }
            }
            size_t npos = line.find("=");
            if(npos != std::string::npos){
                std::string key = line.substr(0, npos);
                std::string value = line.substr(npos + 1);

                // UI Module parsing >>
                if(hasModule){
                    key.erase(0, 1);
                    if(key == "position"){
                        size_t bpos = value.find("|");
                        if(bpos != std::string::npos){
                            float x = std::stof(value.substr(0, bpos));
                            float y = std::stof(value.substr(bpos + 1));
                            img.local.x = x;
                            img.local.y = y;
                            continue;
                        }
                    }
                    if(key == "texture"){
                        img.texturePath = value;
                        continue;
                    }
                }

                // Main UI settings parsing >>
                if(key == "is-static"){
                    result.locked = (value == "true");
                    continue;
                }
                if(key == "visible"){
                    if(value == "true" || value.empty()) result.visible = true;
                    else result.visible = false;
                    continue;
                }
                if(key == "vector"){
                    size_t bpos = value.find("|");
                    if(bpos != std::string::npos){
                        result.position.x = std::stof(value.substr(0, bpos));
                        result.position.y = std::stof(value.substr(bpos + 1));
                    }
                    continue;
                }
            }
        }
    }
}

void UIManager::update(){

}

void UIManager::handle(){
    
}

void UIManager::render(){
    for(int i = 0; i < uiManager.stash.player.size(); i++){
        if(uiManager.stash.player[i].visible == true){
            uiManager.stash.player[i].render();
        }
    }

    for(int i = 0; i < uiManager.stash.world.size(); i++){
        if(uiManager.stash.world[i].visible == true){
            uiManager.stash.world[i].render();
        }
    }
}

void Stash::turn(std::vector<UI> storage, bool status, int id){
    if(id == -1){
        for(int i = 0; i < storage.size(); i++){
            storage[i].visible = status;
        }
    } else {
        for(int i = 0; i < storage.size(); i++){
            if(storage[i].id == id){
                storage[i].visible = status;
            }
        }
    }
}
