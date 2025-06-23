#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"

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
    destR.h = 32;
    destR.w = 32;
}