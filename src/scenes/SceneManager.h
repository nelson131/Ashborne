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
    std::set<TilemapLayer*> colliders;

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

    Scene Testroom;

    private:
    const char *transform(const char *name);

    SDL_Renderer *renderer;
    Scene *currentScene = nullptr;
    std::set<Scene*> holder;

    TilemapLayer layer1;
    TilemapLayer layer2;
    
};

extern SceneManager sceneManager;

#endif