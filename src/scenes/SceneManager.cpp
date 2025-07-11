#include <iostream>
#include <SDL2/SDL.h>
#include "SceneManager.h"
#include "../utils/Logger.h"

SceneManager::SceneManager(SDL_Renderer *sdl_renderer)
    : renderer(sdl_renderer)
{}

void SceneManager::ikuyo(SDL_Rect &camera){
    if(!currentScene){
        logger.print(logger.ERROR, "No current scene set");
        exit(-1);
    }
    for(Tilemap& tilemap : currentScene->layers){
        tilemap.render(renderer, camera);
    }
}

Scene SceneManager::findSceneById(int id){
    for(const auto& element : scenesKeeper){
        if(element.second == id){
            return element.first;
        }
    }
    logger.print(logger.ERROR, "Failed to find scene by id");
    exit(1);
}

Scene *SceneManager::getCurrentScene(){
    return currentScene;
}

void SceneManager::setCurrentScene(Scene *scene) {
    currentScene = scene;
    logger.print(logger.INFO, scene->name);
}