#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Text.h"
#include "Logger.h"

Text::Text(){

}

void Text::ikuyo(const char *path){
    if(TTF_Init() == -1){
        log.print(log.ERROR, TTF_GetError());
        exit(1);
    }

    font = TTF_OpenFont(path, 24);
    if(!font){
        log.print(log.ERROR, TTF_GetError());
        exit(1);
    }
}

SDL_Texture *Text::create(SDL_Renderer *renderer, const char *message){
    SDL_Surface *surface = TTF_RenderText_Blended(font, message, white);
    if(!surface){
        log.print(log.ERROR, TTF_GetError());
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

void Text::clear(){
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
}