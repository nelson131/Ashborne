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

    std::string moduleTitle = "";
    Vector position = {0, 0};
    Vector size = {0, 0};
    std::string fuck = "";
    std::string message = "";

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
                hasModule = false;
                if(moduleTitle == "image"){
                    auto* img = result.addModule<UIModule::Image>();
                    img->local = position;
                    img->size = size;
                    img->texturePath = fuck;
                    img->init();
                    continue;
                }
                if(moduleTitle == "message"){
                    auto* msg = result.addModule<UIModule::Message>();
                    msg->local = position;
                    msg->size = size;
                    msg->font = fuck;
                    msg->content = message;
                    msg->init();
                    continue;
                }
            }
            if(line[0] == ';' && !hasModule){
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
                pointStash->push_back(std::move(result));

                result= {};
                hasObject = false;
                if(title != nullptr){
                    Logger::print(Logger::SUCCESS, "UI (", objectTitle, ") has been initialized");
                    return;
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
                            position = {x, y};
                            continue;
                        }
                    }
                    if(key == "size"){
                        size_t bpos = value.find("|");
                        if(bpos != std::string::npos){
                            float w = std::stof(value.substr(0, bpos));
                            float h = std::stof(value.substr(bpos + 1));
                            size = {w, h};
                            continue;
                        }
                    }
                    if(key == "texture" || key == "font"){
                        fuck = value;
                        continue;
                    }
                    if(key == "message"){
                        message = value;
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
    Logger::print(Logger::SUCCESS, "UI has been initialized");
    Logger::print(Logger::ERROR, uiManager.stash.player.size(), "|", uiManager.stash.player[0].position.x, ";", uiManager.stash.player[0].position.y);
}

void UIManager::update(){
    for(int i = 0; i < uiManager.stash.player.size(); i++){
        uiManager.stash.player[i].update();
    }
}

void UIManager::render(){
    for(int i = 0; i < uiManager.stash.player.size(); i++){
        if(uiManager.stash.player[i].visible == true){
            uiManager.stash.player[i].render();
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
