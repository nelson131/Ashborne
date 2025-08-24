#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Tilemap.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <set>
#include <vector>

class Npc;

struct Scene {
    const char *name;
    int id;
    std::list<TilemapLayer> layers;
    std::set<TilemapLayer*> colliders;
    std::vector<Npc> npcs;

    bool operator<(const Scene &other) const {
        return id < other.id;
    }
};

class SceneManager {

    public:
    SceneManager();

    void init(SDL_Renderer* r);
    void update();
    void ikuyo();

    void setCurrentScene(Scene *scene);
    Scene *getCurrentScene();
    Scene* findSceneById(int id);

    std::set<Scene*>& getHolder();

    private:
    void loadNPCs();
    const char *transform(const char *name);

    const float SCALE = Config::parse<float>("game_info", "scale");

    SDL_Renderer *renderer;
    Scene *currentScene = nullptr;
    std::set<Scene*> holder;

    Scene Testroom;

    TilemapLayer layer1;
    TilemapLayer layer2;
    
};

extern SceneManager sceneManager;

#endif