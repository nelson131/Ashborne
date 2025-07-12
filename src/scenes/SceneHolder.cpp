#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include "SceneManager.h"

void SceneManager::scenesInit(){
        //Test room
        Tilemap testRoomTileMap;

        std::vector<std::vector<int>> mapSet = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0}
        };

        testRoomTileMap.load("assets/tilemaptest.png", renderer, 2);
        testRoomTileMap.set(mapSet);

        Testroom.name = "Test Room";
        Testroom.id = 0;
        Testroom.layers.clear();
        Testroom.layers.push_back(testRoomTileMap);
        scenesKeeper[Testroom] = Testroom.id;
        //
};