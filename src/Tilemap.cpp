#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tilemap.h"

Tilemap::Tilemap(){
    
}

void Tilemap::render(SDL_Renderer *renderer, SDL_Rect &fuckingCamera){
    if (!tileset) {
        logger.print(logger.ERROR, "Failed to render this tileset");
        exit(1);
    }

    for(int y = 0; y<map.size(); y++){
        for(int x = 0; x<map[y].size(); x++){
            SDL_Rect srcRect = {
                (map[y][x] % tilesPerRow) * 32,
                (map[y][x] / tilesPerRow) * 32,
                32,
                32
            };

            SDL_Rect dstRect = {
                x * 32 - fuckingCamera.x,
                y * 32 - fuckingCamera.y,
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

void Tilemap::load(const  char *filePath, SDL_Renderer *renderer, int tilesSize){
    SDL_Surface *surface = IMG_Load(filePath);

    if(!surface) {
        //logger.print(logger.ERROR, "Failed to load surface");
        std::cout << IMG_GetError() << std::endl;
        std::cout << SDL_GetError() << std::endl;
        exit(1);
    }

    tileset = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(!tileset){
        //logger.print(logger.ERROR, "Failed to load tileset");
        std::cout << IMG_GetError() << std::endl;
        std::cout << SDL_GetError() << std::endl;
        exit(1);
    }

    this->tilesPerRow = tilesSize;
}