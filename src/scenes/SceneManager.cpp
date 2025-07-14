#include <iostream>
#include <SDL2/SDL.h>
#include "SceneManager.h"
#include "../utils/Logger.h"

SceneManager::SceneManager(SDL_Renderer *sdl_renderer)
    : renderer(sdl_renderer)
{}

void SceneManager::ikuyo(SDL_Rect &camera){
    if(!currentScene){
        Logger::print(Logger::ERROR, "No current scene set");
        exit(-1);
    }
    for(Tilemap& tilemap : currentScene->layers){
        tilemap.render(renderer, camera);
    }
}

const Scene& SceneManager::findSceneById(int id){
    for(const auto& scene : scenesKeeper){
        if(scene.id == id){
            return scene;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find scene by id");
    exit(1);
}

Scene *SceneManager::getCurrentScene(){
    return currentScene;
}

void SceneManager::setCurrentScene(Scene *scene) {
    currentScene = scene;
    Logger::print(Logger::INFO, "Current scene is: ", scene->name);
}