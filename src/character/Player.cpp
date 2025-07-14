#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"
#include "../game/ItemManager.h"
#include "../alg/Vector.h"

Player::Player(){

}

void Player::init(SDL_Renderer *renderer){
    ePlayer.create(0, 0, texturePath, "Player", true, true, true);
}

void Player::display(SDL_Renderer *renderer){
    ePlayer.render(camera);
}
    
void Player::update(){
    ePlayer.update();
    //camera.x = getX() + destR.w/2 - screen_width/2;
    //camera.y = getY() + destR.h/2 - screen_height/2;
}


void Player::handleInput(){
    speed = config.parse<float>("player_info", "speed");
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    ePlayer.velocity = {0, 0};

    if(keys[SDL_SCANCODE_W]){
        ePlayer.velocity.y -= speed;
    }
    if(keys[SDL_SCANCODE_A]){
        ePlayer.velocity.x -= speed;
    }
    if(keys[SDL_SCANCODE_S]){
        ePlayer.velocity.y += speed;
    }
    if(keys[SDL_SCANCODE_D]){
        ePlayer.velocity.x += speed;
    }
    
}

SDL_Rect &Player::getCamera(){
    return camera;
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