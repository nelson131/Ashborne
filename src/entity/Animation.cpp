#include "Animation.h"
#include "EntityHolder.h"
#include "../TextureManager.h"
#include "../utils/Logger.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

Animation::Animation(){

}

void Animation::fps(int fps){
    frameTime = fps;
}

std::set<AnimSet>& Animation::getKeeper(){
    return keeper; 
}

void Animation::setup(std::string name){
    std::ifstream file("resources/animations.ini");
    if(!file){
        Logger::print(Logger::ERROR, "Failed to open animations.ini");
        return;
    }

    for(char& c : name){
        if(c >= 'A' && c <= 'Z'){
            c += 32;
        }
    }

    std::string line;
    std::string object = "[" + name + "]";
    AnimSet result = AnimSet{};
    bool hasObject = false;
    while(getline(file, line)){
        if(line.empty() || line[0] == '#') continue;
        if(line[0] == '['){
            hasObject = (line == object);
            continue;
        }
        if(hasObject){
            if(line[0] == ';') break;
            size_t pos = line.find('=');
            if(pos != std::string::npos){
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                if(value.empty()) continue;
                result.isFlipped = (value[0] == 'f');
                if(value[0] == 'f'){
                    size_t bpos = value.find("->");
                    if(bpos != std::string::npos){
                        result.type = toTypeFrom(key);

                        std::string k = value.substr(bpos + 2);
                        AnimType t = toTypeFrom(k);
                        for(const AnimSet& set : keeper){
                            if(set.type == t){
                                result.path = set.path;
                                result.cells = set.cells;
                                result.texture = TextureManager::load(result.path.c_str(), eHolder.getRenderer());
                                keeper.insert(result);
                                continue;
                            }
                        }
                    }
                } else {
                    size_t bpos = value.find('|');
                    if(bpos != std::string::npos){
                        int cells = std::stoi(value.substr(0, bpos));
                        std::string path = value.substr(bpos + 1);
                        result.type = toTypeFrom(key);
                        result.path = "assets/" + path;
                        result.cells = cells;
                        result.texture = TextureManager::load(result.path.c_str(), eHolder.getRenderer());
                        keeper.insert(result);
                    }
                }
            }
        }
    }
}

void Animation::play(SDL_Rect &srcRect, SDL_Texture*& t, SDL_RendererFlip& flip){
    Uint32 now = SDL_GetTicks();

    if(keeper.empty()){
        Logger::print(Logger::ERROR, "Anim keeper is empty");
        return;
    }

    if(lastAnim != active){
        AnimSet set = findSetBy(active);
        if(!set.texture){
            Logger::print(Logger::ERROR, "Failed to play anim cause texture in set is null");
            return;   
        }
        if(set.isFlipped){
            flip = SDL_FLIP_HORIZONTAL;
        } else {
            flip = SDL_FLIP_NONE;
        }

        t = set.texture;
        srcRect = {0, 0, 32, 32};
    }

    if(!frameTime || frameTime < 0){
        Logger::print(Logger::ERROR, "Failed to get fps of animation");
    }

    if(now - lastFrameTime > frameTime){
        currentFrame = (currentFrame + 1) % findSetBy(active).cells;
        lastFrameTime = now;
    }

    srcRect.x = currentFrame * 32;
    srcRect.y = 25;

    srcRect.w = 32;
    srcRect.h = 34;

    lastAnim = active;
}

AnimType Animation::getActive(){
    return active;
}

void Animation::setActive(AnimType anim){
    active = anim;
}

AnimType Animation::toTypeFrom(std::string key){
    static std::unordered_map<std::string, AnimType> const table = {
        {"IDLE_UP", AnimType::IDLE_UP},
        {"IDLE_DOWN", AnimType::IDLE_DOWN},
        {"IDLE_LEFT", AnimType::IDLE_LEFT},
        {"IDLE_RIGHT", AnimType::IDLE_RIGHT}
    };
    auto it = table.find(key);
    if(it != table.end()){
        return it->second;
    } else {
        Logger::print(Logger::ERROR, "Failed to convert to animation type from string");
        return AnimType::IDLE_UP;
    }
}

const AnimSet& Animation::findSetBy(AnimType& t) const{
    for(const AnimSet& set : keeper){
        if(set.type == t){
            return set;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find set by anim type");
    exit(-1);
}