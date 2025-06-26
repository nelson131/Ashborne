#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Ashborne.h"
#include "character/Player.h"
#include "Tilemap.h"

Ashborne::Ashborne(){
    
}

void Ashborne::game_init(const char *title, int x, int y, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
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

      int a = 2;
    std::vector<std::vector<int>> mapSet = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0}
    };

    tilemap.set(mapSet);
    tilemap.load("assets/tilemaptest.png", renderer, a);

   
}

void Ashborne::eventManager(){
    while(SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:
                run = false;
                break;
            default:
                break;
        }
    }
}

void Ashborne::render(){
    SDL_RenderClear(renderer);
    //...
    tilemap.render(renderer);
    player.display(renderer);
    //...
    SDL_RenderPresent(renderer);
}

void Ashborne::update(){
    count++;

    player.handleInput();
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

