#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "utils/Logger.h"

#define TILE_EMPTY 0

class TilemapLayer {

    public:
    TilemapLayer();

    void init(int id, bool collisble);

    void load(const char *filePath, SDL_Renderer *renderer, int tilesSize);
    void render(SDL_Renderer *renderer, SDL_Rect &camera);
    void set(std::vector<std::vector<int>> &mapSet);

    bool isBlocked(float x, float y);

    int id;
    bool operator<(const TilemapLayer& other) const {
        return id < other.id;
    }

    private:
    SDL_Texture *tileset;
    std::vector<std::vector<int>> map;
    
    int tilesPerRow;

    bool isCollisible;
};

#endif