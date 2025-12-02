#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Tilemap.h"
#include "../utils/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Npc;

struct Scene {
    std::string name;
    int id;
    std::vector<TilemapLayer> layers;
    std::vector<TilemapLayer> colliders;
    std::vector<Npc> npcs;
};

class SceneManager {

    public:
    SceneManager();

    void init(SDL_Renderer* r, int id);
    void update();
    void ikuyo();

    void setCurrentScene(Scene* scene);
    Scene* getCurrentScene();
    Scene* findSceneByName(const char* name);
    Scene* findSceneById(int id);

    std::vector<Scene>& getHolder();

    private:
    void loadNPCs();
    const char *transform(const char *name);

    const float SCALE = Config::parse<float>("game_info", "scale");

    SDL_Renderer *renderer;
    Scene *currentScene = nullptr;
    std::vector<Scene> holder;

    Scene Testroom;
};

extern SceneManager sceneManager;

#endif