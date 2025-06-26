#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../utils/Config.h"

class Player {

    public:
    Player();

    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void update();

    void handleInput();

    private:
    Config config;

    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    
    float x, y;
    float speed;
    const char *texturePath = "assets/playertest.png";
    
};

#endif