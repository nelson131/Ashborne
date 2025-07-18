#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <set>
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

    void scenesInit();
    void ikuyo(SDL_Rect &camera);

    void setCurrentScene(Scene *scene);
    Scene *getCurrentScene();

    const Scene& findSceneById(int id) const;

    Scene Testroom;


    private:
    Tilemap tilemap;

    SDL_Renderer *renderer;
    Scene *currentScene = nullptr;
    std::set<Scene> scenesKeeper;
    
};

#endif