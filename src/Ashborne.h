#ifndef ASHBORNE_H
#define ASHBORNE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ashborne {
    
    public:
    Ashborne();

    void game_init(const char *title, int x, int y, int width, int height, bool fullscrean);
    void eventManager();
    void update();
    void render();
    void exit();

    bool isRunning();

    private:
    int count = 0;
    bool run;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

};

#endif