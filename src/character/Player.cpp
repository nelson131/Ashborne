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
    destR.h = config.config_parseInt("player_info", "height");
    destR.w = config.config_parseInt("player_info", "width");
}


void Player::handleInput(){
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

std::array<int, 6> Player::getPlayerStats(){
    return player_stats;
}

int Player::getHP(){
    return player_stats[0];
}

int Player::getMana(){
    return player_stats[1];
}

int Player::getPhysDamage(){
    return player_stats[2];
}

int Player::getMagicDamage(){
    return player_stats[3];
}

int Player::getPhysRes(){
    return player_stats[4];
}

int Player::getMagicRes(){
    return player_stats[5];
}

void Player::stats_update(){
    for(int i = 0; i<player_stats.size(); i++){
        player_stats[i] += itemManager.update_parameters()[i];
    };
}