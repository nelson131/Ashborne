#ifndef TILEMAP_H
#define TILEMAP_H

#include "utils/Logger.h"
#include "utils/Config.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#define TILE_EMPTY 0

class TilemapLayer {

    public:
    TilemapLayer();

    void init(bool collidable);
    void render(SDL_Renderer *renderer);

    void load(const char *filePath, SDL_Renderer *renderer, int tilesSize);

    void set(std::vector<std::vector<int>> &mapSet);
    void setFromCSV(const char *csvName, const char *keyTitle);
    std::vector<std::vector<int>> get();

    void debug();

    bool isBlocked(float x, float y);
    bool& isCollidable();

    int id;
    bool operator<(const TilemapLayer& other) const {
        return id < other.id;
    }

    private:
    SDL_Texture *tileset;
    std::vector<std::vector<int>> map;
    
    int tilesPerRow;
    int SCALE = Config::parse<float>("game_info", "scale");

    bool collidable = false;
};

#endif