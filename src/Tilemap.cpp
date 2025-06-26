#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tilemap.h"

Tilemap::Tilemap(){
    
}

void Tilemap::render(SDL_Renderer *renderer){
    for(int y = 0; y<map.size(); y++){
        for(int x = 0; x<map[y].size(); x++){
            SDL_Rect srcRect = {
                (map[y][x] % tilesPerRow) * 32,
                (map[y][x] / tilesPerRow) * 32,
                32,
                32
            };

            SDL_Rect dstRect = {
                x * 32,
                y * 32,
                32,
                32
            };

            SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
        }
    }
}

void Tilemap::set(std::vector<std::vector<int>> &mapSet){
    map = mapSet;
}

void Tilemap::load(const  char *filePath, SDL_Renderer *renderer, int &tilesSize){
    SDL_Surface *surface = IMG_Load(filePath);
    tileset = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    this->tilesPerRow = tilesSize;
}