#include <iostream>
#include <SDL2/SDL.h>
#include <set>
#include "SceneManager.h"
#include "../entity/Npc.h"
#include "../utils/Logger.h"

SceneManager sceneManager;

SceneManager::SceneManager(){
    
}

void SceneManager::init(SDL_Renderer* r){
    renderer = r;
    //Test room ->
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
    // ^^^

    loadNPCs();
    Logger::print(Logger::SUCCESS, "Scene manager initialized");
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

Scene* SceneManager::findSceneById(int id){
    for(Scene *scene : holder){
        if(scene->id == id){
            return scene;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find scene by id");
    exit(1);
}

Scene *SceneManager::getCurrentScene(){
    return sceneManager.currentScene;
}

void SceneManager::setCurrentScene(Scene *scene) {
    sceneManager.currentScene = scene;
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
    Npc object;
    int sceneId, width, height;
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
            sceneId, width, height, x, y, name, filePath, visionr = 0;
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