#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Ashborne.h"
#include "character/Player.h"
#include "Tilemap.h"
#include "scenes/SceneManager.h"
#include "entity/EntityHolder.h"
#include "item/ItemHolder.h"
#include "entity/Npc.h"
#include "entity/Entity.h"
#include "utils/Tile.h"

Ashborne::Ashborne(){

}

void Ashborne::init(const char *title, int x, int y, int width, int height, bool fullscreen){
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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    eHolder.init(renderer);

    sceneManager.scenesInit(renderer);
    sceneManager.setCurrentScene(&sceneManager.Testroom);

    player.init(renderer);

    itemHolder.init();
    
    Tile t(2, 0, 64);
    npc.spawn(t.getWorldX(), t.getWorldY(), "assets/playertest.png", "npc", Entity::Relationship::NEUTRAL, true, true, false, true);

    npc.setPathing(true);
    npc.addDot(Tile(4, 2, 64));
    npc.addDot(Tile(4, 4, 64));
    npc.addDot(Tile(4, 10, 64));
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
    sceneManager.ikuyo();
    player.display(renderer);
    npc.render();
    //...
    SDL_RenderPresent(renderer);
}

void Ashborne::update(){
    count++;

    player.handleInput();
    player.update();
    npc.update();

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

