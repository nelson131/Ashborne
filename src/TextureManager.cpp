#include "TextureManager.h"
#include "utils/Logger.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TextureManager::TextureManager(){

}

SDL_Texture* TextureManager::load(const char *pathToFIle, SDL_Renderer *renderer){
    SDL_Surface *tempSurface = IMG_Load(pathToFIle);
    if(!tempSurface){
        Logger::print(Logger::ERROR, "Failed to load surface (texturemanager)", IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if(!texture){
        Logger::print(Logger::ERROR, "Failed to load texture (texturemanager)", IMG_GetError());
    }

    return texture;
}
