#include "Tilemap.h"
#include <iostream>

Tileset::Tileset()
    : texture(nullptr), renderer(nullptr), amount(0), size(32)
{
    
}

void Tileset::load(std::string filePath){
    this->texture = TextureManager::load(filePath.c_str(), renderer);
}


Tilemap::Tilemap(){

}

void Tilemap::init(SDL_Renderer* renderer, bool collidable){
    this->renderer = renderer;
    this->collidable = collidable;
}

void Tilemap::render(){
    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[0].size(); x++){
            if(map[y][x] == TILE_EMPTY) continue;

            SDL_Rect srcRect = {
                ((map[y][x]-1) % tileset.amount) * 32,
                ((map[y][x]-1) / tileset.amount) * 32,
                32,
                32
            };

            SDL_Rect dstRect = {
                x * 32 * SCALE - camera.get().x,
                y * 32 * SCALE - camera.get().y,
                32 * SCALE,
                32 * SCALE
            };

            SDL_RenderCopy(renderer, tileset.texture, &srcRect, &dstRect);
        }
    }
}

bool Tilemap::isCollidable(){
    return collidable;
}