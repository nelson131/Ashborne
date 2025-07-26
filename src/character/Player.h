#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include "../utils/Config.h"
#include "../utils/Cursor.h"
#include "../entity/Entity.h"

class Player {

    public:
    Player();

    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void update();
    void handleInput();
    
    void updateMousePos();

    SDL_Rect &getCamera();

    private:
    float getSpeed() const;

    Entity player;
    Cursor cursor;

    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    
    const char *texturePath = "assets/playertestanim.png";

    SDL_Rect camera = {0, 0, 640, 480};
    int screen_width = Config::parse<int>("game_info", "screen_width");
    int screen_height = Config::parse<int>("game_info", "screen_height");
};

#endif