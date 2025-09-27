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

    std::string line;

    UI result = {};
    std::string objectTitle = "";
    bool hasObject = false;
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
        if(hasObject){
            if(line[0] == ';'){
                std::vector<UI>* pointStash = nullptr;
                switch (type){
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
                result = {};
                hasObject = false;

                if(title == nullptr){
                    return;
                }
            }
            size_t npos = line.find("=");
            if(npos != std::string::npos){
                std::string key = line.substr(0, npos);
                std::string value = line.substr(npos + 1);

                if(key == "is-static"){
                    result.locked = (value == "true");
                    continue;
                }
                if(key == "size"){
                    size_t bpos = value.find("|");
                    if(bpos != std::string::npos){
                        result.size.x = std::stof(value.substr(0, bpos));
                        result.size.y = std::stof(value.substr(bpos + 1));
                    }
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
                if(key == "texture-path"){
                    result.texturePath = "assets/" + value;
                    continue;
                }
            }
        }
    }

    /*
    test.id = 1;
    test.title = "test";
    test.texturePath = "assets/playertest.png";
    test.size = {200, 200};
    test.visible = true;

    test.init(); */
}

void UIManager::update(){

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
