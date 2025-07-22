#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include "SceneManager.h"
#include "../utils/Logger.h"

void SceneManager::scenesInit(SDL_Renderer *r){
        renderer = r;
        //Test room
        TilemapLayer layer1;
        layer1.init(666, false);

        std::vector<std::vector<int>> mapSet1 = {
        {1, 1, 1, 1, 1, 0},
        {2, 2, 1, 1, 1, 0},
        {1, 2, 0, 2, 1, 0},
        {1, 1, 2, 2, 1, 0}
        };

        layer1.load("assets/tilemaptest.png", renderer, 2);
        layer1.set(mapSet1);

        TilemapLayer layer2;
        layer2.init(777, true);

        std::vector<std::vector<int>> mapSet2 = {
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
        };

        layer2.load("assets/tilemaptest.png", renderer, 2);
        layer2.set(mapSet2);
        Testroom.name = "Test Room";
        Testroom.id = 0;
        Testroom.layers.clear();
        Testroom.layers.push_back(layer1);
        Testroom.layers.push_back(layer2);
        getHolder().insert(&Testroom);
        getCmaps().insert(&layer2);
        //
        Logger::print(Logger::SUCCESS, "Scene manager initialized");
};

std::set<Scene*>& SceneManager::getHolder(){
        return sceneManager.holder;
}

std::set<TilemapLayer*>& SceneManager::getCmaps(){
        return sceneManager.cmaps;
}
