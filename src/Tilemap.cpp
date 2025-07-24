#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include "Tilemap.h"

TilemapLayer::TilemapLayer(){
    
}

void TilemapLayer::init(bool collisible){
    isCollidable = collisible;
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

void TilemapLayer::setFromCSV(const char *csvName){
    std::string path = "resources/maps/" + std::string(csvName);
    std::ifstream file (path);
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "CSV map does not exist");
        return;
    }

    std::vector<std::vector<int>> result;
    int y = 0;
    std::string line;
    while(getline(file, line)){
        if(line.empty() || line[0] == ' ' || line[0] == '#'){
            continue;
        }
        
        for(int i = 0; i < line.length(); i++){
            int x = 0;
            if(x != 0 && line[i] == ' ' && line[i+1] == ' ') break;
            if(line[i] == ' ') continue;
            result[y][x] = line[i];
            x++;
        }
        y++;
    }

    set(result);
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
    if(!isCollidable){
        Logger::print(Logger::ERROR, "Tried to check a blocked tile but tilemap is not collidable");
        return false;
    }

    if(map.empty()){
        Logger::print(Logger::ERROR, "Collision map is empty");
        return false;
    }

    int tileX = x / 32;
    int tileY = y / 32;

    if(tileY < 0 || tileY >= map.size()) return false;
    if(tileX < 0 || tileX >= map[0].size()) return false;

    return map[tileY][tileX] != TILE_EMPTY;
}