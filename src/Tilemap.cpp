#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>
#include "Tilemap.h"
#include "Camera.h"

TilemapLayer::TilemapLayer(){
    
}

void TilemapLayer::init(bool collisible){
    isCollidable = collisible;
}

void TilemapLayer::render(SDL_Renderer *renderer){
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
                x * 32 * SCALE - camera.get().x,
                y * 32 * SCALE - camera.get().y,
                32 * SCALE,
                32 * SCALE
            };

            SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
        }
    }
}

void TilemapLayer::set(std::vector<std::vector<int>> &mapSet){
    map = mapSet;
}

void TilemapLayer::setFromCSV(const char *csvName, const char *keyTitle){
    std::string path = "resources/maps/" + std::string(csvName) + ".csv";
    std::ifstream file(path);
    if(!file.is_open()){
        Logger::print(Logger::ERROR, "CSV map (", csvName, "does not exist");
        return;
    }

    std::vector<std::vector<int>> result;
    int y = 0;

    std::string title = '[' + std::string(keyTitle) + ']';
    std::string line;
    bool hasTitle = false;

    while(getline(file, line)){
        if(line.empty() || line[0] == ' ' || line[0] == '#'){
            continue;
        }
        
        if(line[0] == '['){
            hasTitle = (line == title);
            continue;
        }

        if(hasTitle){
            std::vector<int> row;
            std::stringstream ss(line);
            int value;
            while(ss >> value){
                row.push_back(value);
            }
            if(!row.empty()){
                result.push_back(row);
            }
        }
    }
    
    map = result;
}

void TilemapLayer::debug(){
    if(map.empty()){
        Logger::print(Logger::ERROR, "Map is empty");
        return;
    }
    Logger::print(Logger::DEBUG, "Tileset: ");
    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[y].size(); x++){
            std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
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

    int tileX = x / (32 * SCALE);
    int tileY = y / (32 * SCALE);

    if(tileY < 0 || tileY >= map.size()) return false;
    if(tileX < 0 || tileX >= map[0].size()) return false;

    return map[tileY][tileX] != TILE_EMPTY;
}