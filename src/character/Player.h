#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include "../utils/Config.h"

class Player {

    public:
    Player();

    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void update();
    void handleInput();

    float getX();
    float getY();
    SDL_Rect &getCamera();

    std::array<int, 6> getPlayerStats();

    int getHP();
    int getMana();
    int getPhysDamage();
    int getMagicDamage();
    int getPhysRes();
    int getMagicRes();

    void statsUpdate();

    private:
    Config config;

    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    
    float speed;
    const char *texturePath = "assets/playertest.png";

    SDL_Rect camera = {0, 0, 640, 480};
    int screen_width = config.parseInt("game_info", "screen_width");
    int screen_height = config.parseInt("game_info", "screen_height");

    std::array<int, 6> playerStats;

};

#endif