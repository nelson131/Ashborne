#include "UIManager.h"
#include "UI.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <memory>
#include <unordered_map>

UIManager uiManager;

UIManager::UIManager(){

}

void UIManager::init(Stash::InitType type, const char* title){
    std::string path = "resources/ui/";
    switch (type) {
        case Stash::InitType::PLAYER:
            path += "player.ini";
            break;
        case Stash::InitType::WORLD:
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
            result.title = objectTitle;
            
            if(title != nullptr){
                hasObject = (objectTitle == title);
            }
            else hasObject = true;
        }
        if(line[0] == '>'){
            hasModule = true;

            moduleTitle = line;
            moduleTitle.erase(0, 1);
            moduleTitle.erase(0, 1);
            moduleTitle.erase(moduleTitle.size() - 1);
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
                    case Stash::InitType::PLAYER:
                        pointStash = &uiManager.stash.player;
                        break;
                    case Stash::InitType::WORLD:
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
                    if(key == "content"){
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
                    if(value[0] == '*'){
                        value.erase(0, 1);
                        size_t bpos = value.find("|");
                        if(bpos != std::string::npos){
                            std::string first = value.substr(0, bpos);
                            std::string second = value.substr(bpos + 1);
                            ikuyoPosition(result.position, stash.toPosTypeFrom(first));
                            ikuyoPosition(result.position, stash.toPosTypeFrom(second));
                        } else {
                            ikuyoPosition(result.position, stash.toPosTypeFrom(value));
                        }
                    } else {
                        size_t bpos = value.find("|");
                        if(bpos != std::string::npos){
                            result.position.x = std::stof(value.substr(0, bpos));
                            result.position.y = std::stof(value.substr(bpos + 1));
                        }
                    }
                    continue;
                }
            }
        }
    }
    Logger::print(Logger::SUCCESS, "UI has been initialized");
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

void UIManager::ikuyoPosition(Vector& position, Stash::PositionType type){
    float windowHeight = Config::parse<float>("game_info", "screen_height");
    float windowWidth = Config::parse<float>("game_info", "screen_width");
    switch(type){
        case Stash::PositionType::RIGHT:
            position.x = windowWidth - position.x;
            break;
        case Stash::PositionType::LEFT:
            position.x = position.x;
            break;
        case Stash::PositionType::TOP:
            position.y = position.y;
            break;
        case Stash::PositionType::DOWN:
            position.y = windowHeight - position.y;
            break;
        case Stash::PositionType::CENTER:
            position.x += windowWidth/2 + position.x;
            position.y += windowHeight/2 + position.y;
            break;
        default:
            break;    
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

Stash::PositionType Stash::toPosTypeFrom(std::string& value){
    static std::unordered_map<std::string, PositionType> const table = {
        {"RIGHT", PositionType::RIGHT},
        {"LEFT", PositionType::LEFT},
        {"TOP", PositionType::TOP},
        {"DOWN", PositionType::DOWN},
        {"CENTER", PositionType::CENTER}
    };
    auto it = table.find(value);
    if(it != table.end()){
        return it->second;
    } else {
        Logger::print(Logger::ERROR, "Failed to convert to animation type from string");
        return PositionType::CENTER;
    }
}