#include <iostream>
#include <SDL2/SDL.h>
#include "SceneManager.h"
#include "../utils/Logger.h"

SceneManager sceneManager;

SceneManager::SceneManager(){
    
}

void SceneManager::ikuyo(){
    if(!sceneManager.currentScene){
        Logger::print(Logger::ERROR, "No current scene set");
        exit(-1);
    }
    for(TilemapLayer& layer : sceneManager.currentScene->layers){
        layer.render(renderer);
    }
}

const Scene* SceneManager::findSceneById(int id) const{
    for(const Scene *scene : holder){
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
    Logger::print(Logger::INFO, "Current scene is: ", scene->name);
}