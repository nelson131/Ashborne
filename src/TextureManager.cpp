#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

TextureManager::TextureManager(){

}

void TextureManager::load(const char *pathToFIle, SDL_Renderer *renderer){
    SDL_Surface *tempSurface = IMG_Load(pathToFIle);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}
