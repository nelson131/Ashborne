#include "SceneManager.h"
#include "../entity/Npc.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <set>

SceneManager sceneManager;

SceneManager::SceneManager(){
    
}

void SceneManager::init(SDL_Renderer* r, int id){
    this->renderer = r;

    std::ifstream file("resources/scenes.ini");
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "Failed to open scenes.ini");
        return;
    }

    std::string line = "";

    Scene result = {};
    int sceneId = -1;
    std::string sceneName = "";
    bool hasObject = false;

    TilemapLayer layer = {};
    std::string csvName = "";
    int size = 0;
    bool hasLayer = false;
    while(getline(file, line)){
        if(line[0] == '#' || line.empty()) continue;
        if(line[0] == ';' && !hasLayer){
            result.name = sceneName.c_str();
            result.id = sceneId;
            sceneManager.holder.push_back(result);
            Logger::print(Logger::SUCCESS, "Scene -> ", result.name, " has been initializated");
            return;
        }
        if(line[0] == '['){
            line.erase(0, 1);
            line.erase(line.size() - 1);
            int lineId = std::stoi(line);
            if(id == lineId){
                hasObject = true;
                sceneId = lineId;
            } else {
                hasObject = false;
            }
            continue;
        }
        if(hasObject){
            if(line[0] == '>'){
                hasLayer = true;
                line.erase(0, 1);
                line.erase(line.size() - 1);
                line.erase(0, 1);
                csvName = line;
            }
            if(line[1] == ';'){
                layer.setFromCSV(transform(sceneName.c_str()), csvName.c_str());
                result.layers.push_back(layer);
                if(layer.isCollidable()) result.colliders.push_back(layer);
                layer = {};
                hasLayer = false;
                continue;
            }
            size_t pos = line.find("=");
            if(pos != std::string::npos){
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                if(hasLayer){
                    if(key[0] == ' ') key.erase(0, 1);
                    if(key == "collidable"){
                        if(value == "true"){
                            layer.init(true);
                            continue;
                        }
                        layer.init(false);
                    }
                    if(key == "size"){
                        size = std::stoi(value);
                        continue;
                    }
                    if(key == "path"){
                        layer.load(value.c_str(), this->renderer, size);
                        continue;
                    }
                }

                if(key == "name"){
                    sceneName = value;
                    continue;
                }
            }
        }
    }
}

void SceneManager::update(){
    for(Npc& npc : sceneManager.getCurrentScene()->npcs){
        npc.update();
    }
}

void SceneManager::ikuyo(){
    if(!sceneManager.currentScene){
        Logger::print(Logger::ERROR, "No current scene set");
        exit(-1);
    }
    for(TilemapLayer& layer : sceneManager.currentScene->layers){
        layer.render(renderer);
    }

    for(Npc& npc : sceneManager.currentScene->npcs){
        npc.render();
    }
}

Scene* SceneManager::getCurrentScene(){
    return sceneManager.currentScene;
}

Scene* SceneManager::findSceneByName(const char* name){
    if(!name){
        Logger::print(Logger::ERROR, "Failed to find scene by name cause name is nullptr");
        return nullptr;
    }

    for(Scene& scene : sceneManager.holder){
        if(scene.name == name){
            return &scene;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find scene by name");
    return nullptr;
}

Scene* SceneManager::findSceneById(int id){
    for(Scene& scene : sceneManager.holder){
        if(scene.id == id){
            return &scene;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find scene by id");
    return nullptr;
}

void SceneManager::setCurrentScene(Scene* scene) {
    sceneManager.currentScene = scene;
    loadNPCs();
    for(Npc& npc : scene->npcs){
        npc.spawn();
    }
    
    Logger::print(Logger::INFO, "Current scene is: ", scene->name);
}

void SceneManager::loadNPCs(){
    std::ifstream file("resources/npc.ini");
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "Failed to find npc.ini file");
        return;
    }
    if(currentScene == nullptr){
        Logger::print(Logger::ERROR, "Failed to load npcs cause current scene is nullptr");
        return;
    }
    int sceneId = currentScene->id;

    Npc object;
    int width, height;
    float x, y;
    std::string name, filePath;
    bool animated, debugmode, pathing;
    float visionr;
    std::vector<Vector> dots;

    std::string line;
    bool hasObject = false;
    while(getline(file, line)){
        if(line.empty() || line[0] == '#') continue;
        if(line[0] == ';'){
            object.setSpawnPars(x, y, width, height, filePath, name, animated, debugmode);
            object.setBehavior(pathing, visionr);
            if(pathing) object.addDots(dots);
            findSceneById(sceneId)->npcs.push_back(object);

            hasObject = false;
            object = Npc{};
            sceneId = 0; width = 0; height = 0;
            x = 0; y = 0;
            name.clear();
            filePath.clear();
            visionr = 0;
            dots.clear();
            continue;
        }
        if(line[0] == '['){
            hasObject = true;
            name = line.substr(1, line.size() - 2);
            continue;
        }
        if(hasObject){
            size_t pos = line.find("=");
            if(pos != std::string::npos){
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                if(key == "scene-id"){
                    sceneId = std::stoi(value);
                    continue;
                }
                if(key == "width"){
                    width = std::stoi(value);
                    continue;
                }
                if(key == "height"){
                    height = std::stoi(value);
                    continue;
                }
                if(key == "spawn"){
                    size_t p = value.find(",");
                    int px = std::stoi(value.substr(0, p));
                    int py = std::stoi(value.substr(p + 1));
                    Tile t(px, py, width * SCALE);
                    x = t.getWorldX();
                    y = t.getWorldY();
                    continue;
                }
                if(key == "path"){
                    filePath = value;
                    continue;
                }
                if(key == "animated"){
                    animated = (value == "true");
                    continue;
                }
                if(key == "debugmode"){
                    debugmode = (value == "true");
                    continue;
                }
                if(key == "vision-radius"){
                    visionr = atof(value.c_str());
                    continue;
                }
                if(key == "pathing"){
                    pathing = (value == "true");
                    continue;
                }
                if(key == "dots" && pathing){
                    std::stringstream ss(value);
                    std::string coord;
                    while(std::getline(ss, coord, '|')){
                        size_t t = coord.find(",");
                        if(t != std::string::npos){
                            int dx = std::stoi(coord.substr(0, t));
                            int dy = std::stoi(coord.substr(t + 1));
                            dots.emplace_back(dx, dy);
                        }
                    }
                }
            }
        }
    }
}

std::vector<Scene>& SceneManager::getHolder(){
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