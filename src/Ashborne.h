#ifndef ASHBORNE_H
#define ASHBORNE_H

#include "character/Player.h"
#include "Tilemap.h"
#include "scenes/SceneManager.h"
#include "entity/Npc.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

class Ashborne {
    
    public:
    Ashborne();

    void init(const char *title, int x, int y, int width, int height, bool fullscreen);
    void eventManager();
    void update();
    void render();
    void exit();

    bool isRunning();

    private:
    Player player;
    TilemapLayer tilemap;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    int count = 0;
    bool run;
    
};

#endif