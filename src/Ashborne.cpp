#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Ashborne.h"
#include "character/Player.h"
#include "Tilemap.h"
#include "scenes/SceneManager.h"

Ashborne::Ashborne(){

}

void Ashborne::gameInit(const char *title, int x, int y, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

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
    
    sceneManager = std::make_unique<SceneManager>(renderer);
    sceneManager->scenes_init();
    sceneManager->setCurrentScene(&sceneManager->Testroom);

    player.init(renderer);
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
    sceneManager->ikuyo(player.getCamera());
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

