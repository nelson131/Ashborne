#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"
#include "../alg/Vector.h"
#include "../scenes/SceneManager.h"
#include "../Camera.h"
#include "../utils/Tile.h"

Player::Player(){

}

void Player::init(SDL_Renderer *renderer){
    player.create(0, 0, texturePath, "Player", Entity::Relationship::PLAYER, true, true, true, true);

    player.animation.fps(300);
    player.animation.add(Animation::Type::IDLE, 3);

    if(player.hasDebugMode()){
        cursor.init();
    }
}

void Player::display(SDL_Renderer *renderer){
    player.render();

    if(player.hasDebugMode()){
        //cursor.render("X: ", cursor.getWorldX(), " | Y: ", cursor.getWorldY());
        Tile t = Tile::worldToTile(cursor.getWorldX(), cursor.getWorldY(), 64);
        cursor.render("X: ", t.getTileX(), "Y: ", t.getTileY());
    }
}
    
void Player::update(){
    player.update();
    camera.update(player.position.x, player.position.y, player.getWidth());
    

    if(player.hasDebugMode()){
        cursor.update();
    }
}


void Player::handleInput(){
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    player.velocity = {0, 0};

    if(keys[SDL_SCANCODE_W]){
        player.velocity.y -= getSpeed();
    }
    if(keys[SDL_SCANCODE_A]){
        player.velocity.x -= getSpeed();
    }
    if(keys[SDL_SCANCODE_S]){
        player.velocity.y += getSpeed();
    }
    if(keys[SDL_SCANCODE_D]){
        player.velocity.x += getSpeed();
    }
}

float Player::getSpeed() const{
    return static_cast<float>(player.getMoveSpeed());
}