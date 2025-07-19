#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"
#include "../alg/Vector.h"

Player::Player(){

}

void Player::init(SDL_Renderer *renderer){
    player.create(0, 0, texturePath, "Player", true, true, true, true);

    player.animation.fps(300);
    player.animation.add(Animation::Type::IDLE, 3);
}

void Player::display(SDL_Renderer *renderer){
    player.render(camera);
}
    
void Player::update(){
    player.update();
    //camera.x = getX() + destR.w/2 - screen_width/2;
    //camera.y = getY() + destR.h/2 - screen_height/2;
}


void Player::handleInput(){
    speed = config.parse<float>("player_info", "speed");
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    player.velocity = {0, 0};

    if(keys[SDL_SCANCODE_W]){
        player.velocity.y -= speed;
    }
    if(keys[SDL_SCANCODE_A]){
        player.velocity.x -= speed;
    }
    if(keys[SDL_SCANCODE_S]){
        player.velocity.y += speed;
    }
    if(keys[SDL_SCANCODE_D]){
        player.velocity.x += speed;
    }
    
}

SDL_Rect &Player::getCamera(){
    return camera;
}