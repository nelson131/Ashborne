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

    void handleInput();

    private:
    float x, y;
    float speed;
    const char *texturePath = "assets/playertest.png";
    
};

#endif