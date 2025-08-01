#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include "../utils/Config.h"
#include "../utils/Cursor.h"
#include "../entity/Entity.h"
#include "../Camera.h"

class Player {

    public:
    Player();

    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void update();
    void handleInput();
    
    void updateMousePos();

    private:
    Entity player;
    Cursor cursor;

    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    
    const char *texturePath = "assets/player.png";

    int width = Config::parse<int>("player_info", "width");
    int height = Config::parse<int>("player_info", "height");

    int screenWidth = Config::parse<int>("game_info", "screen_width");
    int screenHeight = Config::parse<int>("game_info", "screen_height");

    float getSpeed() const;
};

#endif