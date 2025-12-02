#include "ChunkManager.h"
#include <iostream>
#include <fstream>

ChunkManager::ChunkManager(){

}

void ChunkManager::init(SDL_Renderer* renderer){
    this->renderer = renderer;
}

void ChunkManager::loadSceneByName(const char* name){
    Scene* scene = nullptr;
    if(!name){
        scene = sceneManager.getCurrentScene();
    } else {
        scene = sceneManager.findSceneByName(name);
    }
    loadChunksFromFile(scene);
}

void ChunkManager::loadSceneById(size_t id){
    Scene* scene = nullptr;
    if(id < 0){
        scene = sceneManager.getCurrentScene();
    } else {
        scene = sceneManager.findSceneById(id);
    }
    loadChunksFromFile(scene);
}

void ChunkManager::loadChunksFromFile(Scene* scene){
    std::string name = scene->name;
    for(char& c : name){
        if(c >= 'A' && c<= 'Z'){
            c += 32;
        }
    }

    std::ifstream file("resources/maps" + name + ".ini");
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "Failed to open scene map file -> ", name);
        return;
    }

    std::string line;
    bool hasObject = false;
    while(getline(file, line)){
        if(line[0] == '#' || line.empty()) continue;
        if(line[0] == '['){
            line.erase(0, 1);
            line.erase(line.size() - 1);
        }
    }
}