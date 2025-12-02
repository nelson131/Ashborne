#ifndef CHUNK_H
#define CHUNK_H

#include "Tilemap.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Chunk {
    public:
    Chunk();

    void load(SDL_Renderer* renderer);
    void update();
    void render();

    private:
    SDL_Renderer* renderer = nullptr;

    std::vector<Tilemap> layers;
};

#endif