#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Ashborne.h"
#include "character/Player.h"

Player player;

Ashborne::Ashborne(){
    
}

void Ashborne::game_init(const char *title, int x, int y, int width, int height, bool fullscrean){
    int flags = 0;
    if(fullscrean){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
        title,
        x,
        y,
        width,
        height,
        flags
    );

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(renderer){
        run = true;
    } else {
        run = false;
    }

    player.init(renderer);

}

void Ashborne::eventManager(){
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            run = false;
            break;
        case SDLK_w:
            break;
        case SDLK_a:
            break;
        case SDLK_s:
            break;
        case SDLK_d:
            break;
        default:
            break;
    }
}

void Ashborne::render(){
    SDL_RenderClear(renderer);
    //...
    player.display(renderer);
    //...
    SDL_RenderPresent(renderer);
}

void Ashborne::update(){
    count++;

    player.update();

    //std::cout << count << std::endl;
}

void Ashborne::exit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

}

bool Ashborne::isRunning(){
    return run;
}

