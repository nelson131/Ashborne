#ifndef TILEMAP_H
#define TILEMAP_H

#include "TextureManager.h"
#include "../Camera.h"
#include "../utils/Config.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>

#define TILE_EMPTY 0

struct Tileset {
    Tileset();

    void load(std::string filePath);

    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int amount, size;
};

class Tilemap {
    public:
    Tilemap();

    void init(SDL_Renderer* renderer, bool collidable);
    void render();

    bool isCollidable();

    private:
    Tileset tileset;

    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::vector<std::vector<int>> map;

    bool collidable = false;
    int SCALE = Config::parse<int>("game_info", "scale");
};

#endif