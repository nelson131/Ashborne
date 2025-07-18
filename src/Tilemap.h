#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "utils/Logger.h"

class Tilemap {

    public:
    Tilemap();

    void load(const char *filePath, SDL_Renderer *renderer, int tilesSize);
    void render(SDL_Renderer *renderer, SDL_Rect &camera);
    void set(std::vector<std::vector<int>> &mapSet);

    private:
    SDL_Texture *tileset;
    std::vector<std::vector<int>> map;
    
    int tilesPerRow;
};

#endif