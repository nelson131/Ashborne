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
    std::list<TilemapLayer> layers;

    bool operator<(const Scene &other) const {
        return id < other.id;
    }
};

class SceneManager {

    public:
    SceneManager();

    void scenesInit(SDL_Renderer *r);
    void ikuyo(SDL_Rect &camera);

    void setCurrentScene(Scene *scene);
    Scene *getCurrentScene();
    const Scene* findSceneById(int id) const;

    std::set<Scene*>& getHolder();
    std::set<TilemapLayer*>& getCmaps();

    Scene Testroom;

    private:
    TilemapLayer tilemap;

    SDL_Renderer *renderer;
    Scene *currentScene = nullptr;
    std::set<Scene*> holder;
    std::set<TilemapLayer*> cmaps;
    
};

extern SceneManager sceneManager;

#endif