#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"
#include "../game/ItemManager.h"

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
    destR.h = config.parseInt("player_info", "height");
    destR.w = config.parseInt("player_info", "width");
}


void Player::handleInput(){
    speed = config.parseFloat("player_info", "speed");
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

std::array<int, 6> Player::getPlayerStats(){
    return playerStats;
}

int Player::getHP(){
    return playerStats[0];
}

int Player::getMana(){
    return playerStats[1];
}

int Player::getPhysDamage(){
    return playerStats[2];
}

int Player::getMagicDamage(){
    return playerStats[3];
}

int Player::getPhysRes(){
    return playerStats[4];
}

int Player::getMagicRes(){
    return playerStats[5];
}

void Player::statsUpdate(){
    for(int i = 0; i<playerStats.size(); i++){
        playerStats[i] += itemManager.updateParameters()[i];
    };
}