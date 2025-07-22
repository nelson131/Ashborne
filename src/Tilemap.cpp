#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tilemap.h"

TilemapLayer::TilemapLayer(){
    
}

void TilemapLayer::init(int mapid, bool collisible){
    id = mapid;
    isCollisible = collisible;
}

void TilemapLayer::render(SDL_Renderer *renderer, SDL_Rect &fuckingCamera){
    if (!tileset) {
        Logger::print(Logger::ERROR, "Failed to render this tileset");
        exit(1);
    }

    for(int y = 0; y<map.size(); y++){
        for(int x = 0; x<map[y].size(); x++){

            if(map[y][x] == TILE_EMPTY) continue;

            SDL_Rect srcRect = {
                ((map[y][x]-1) % tilesPerRow) * 32,
                ((map[y][x]-1) / tilesPerRow) * 32,
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

void TilemapLayer::set(std::vector<std::vector<int>> &mapSet){
    map = mapSet;
}

void TilemapLayer::load(const  char *filePath, SDL_Renderer *renderer, int tilesSize){
    SDL_Surface *surface = IMG_Load(filePath);

    if(!surface) {
        Logger::print(Logger::ERROR, "Failed to load surface: ", IMG_GetError(), SDL_GetError());
        exit(1);
    }

    tileset = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(!tileset){
        Logger::print(Logger::ERROR, "Failed to load tileset: ", IMG_GetError(), SDL_GetError());
        exit(1);
    }

    this->tilesPerRow = tilesSize;
}

bool TilemapLayer::isBlocked(float x, float y){
    if(isCollisible){
        if(map.size() == 0){
            Logger::print(Logger::ERROR, "Failed to check collision of map");
            exit(-1);
        }
        int tileX = static_cast<int>(x / 32);
        int tileY = static_cast<int>(y / 32);

        if(tileY < 0 || tileY >= map.size()) return false;
        if(map[tileY].empty()) return false;
        if(tileX < 0 || tileX >= map[tileY].size()) return false;

        return map[static_cast<int>(x / 32)][static_cast<int>(y / 32)] != 0;
    }
    //Logger::print(Logger::ERROR, "Tried to check a blocked tile but tilemap is not collisible");
    return false;
}