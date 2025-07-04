#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <map>
#include <memory>
#include "../Tilemap.h"
#include "../utils/Logger.h"

struct Scene {
    const char *name;
    int id;
    std::list<Tilemap> layers;

    bool operator<(const Scene &other) const {
        return id < other.id;
    }
};

class SceneManager {

    public:
    SceneManager(SDL_Renderer *sdlRenderer);

    void scenes_init();

    void ikuyo();
    Scene findSceneById(int id);

    void setCurrentScene(Scene *scene);
    Scene *getCurrentScene();

    Scene Testroom;


    private:
    SDL_Renderer *renderer;

    Tilemap tilemap;
    Logger logger;

    Scene *currentScene = nullptr;

    std::map<Scene, int> scenesKeeper;
    
};

#endif