#include "Text.h"
#include "Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Text::Text(){

}

void Text::ikuyo(const char *path){
    if(TTF_Init() == -1){
        Logger::print(Logger::ERROR, "Failed to init sdl ttf: ", TTF_GetError());
        exit(1);
    }

    font = TTF_OpenFont(path, 15);
    if(!font){
        Logger::print(Logger::ERROR, "Failed to load font: ", TTF_GetError());
        exit(1);
    }
}

SDL_Texture *Text::create(SDL_Renderer *renderer, const char *message){
    SDL_Surface *surface = TTF_RenderText_Blended(font, message, white);
    if(!surface){
        Logger::print(Logger::ERROR, "Failed to load text surface: ", TTF_GetError());
        exit(1);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
    return texture;    
}

void Text::render(SDL_Renderer *renderer, const char *message){
    texture = create(renderer, message);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::move(float x, float y){
    rect.x = x;
    rect.y = y;
}

void Text::clear(){
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Text::quit(){
    clear();
    if(font){
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}