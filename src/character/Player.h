#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Player {
    public:
    Player();

    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void update();

    private:
    const char *texturePath = "assets/playertest.png";
    
};

#endif