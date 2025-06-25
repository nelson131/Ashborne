#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"

SDL_Texture *texture;
SDL_Rect srcR, destR;

Player::Player(){

}

void Player::init(SDL_Renderer *renderer){

    SDL_Surface *surface = IMG_Load(texturePath);

    if(!surface){
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Player::display(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, texture, NULL, &destR);
}
    
void Player::update(){
    Config config;
    destR.h = config.config_parseInt("player_info", "height");
    destR.w = config.config_parseInt("player_info", "width");
}


void Player::handleInput(){
    Config config;
    speed = config.config_parseFloat("player_info", "speed");
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(keys[SDL_SCANCODE_W]){
        destR.y -= speed;
    }
    if(keys[SDL_SCANCODE_A]){
        destR.x -= speed;
    }
    if(keys[SDL_SCANCODE_S]){
        destR.y += speed;
    }
    if(keys[SDL_SCANCODE_D]){
        destR.x += speed;
    }
}