#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include "SceneManager.h"

void SceneManager::scenes_init(){
        //Test room
        Tilemap testroom_tilemap;

        std::vector<std::vector<int>> mapSet = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0}
        };

        testroom_tilemap.load("assets/tilemaptest.png", renderer, 2);
        testroom_tilemap.set(mapSet);

        Testroom.name = "Test Room";
        Testroom.id = 0;
        Testroom.layers.clear();
        Testroom.layers.push_back(testroom_tilemap);
        scenesKeeper[Testroom] = Testroom.id;
        //
};