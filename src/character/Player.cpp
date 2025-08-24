#include "Player.h"
#include "../TextureManager.h"
#include "../utils/Config.h"
#include "../alg/Vector.h"
#include "../scenes/SceneManager.h"
#include "../Camera.h"
#include "../utils/Tile.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Player::Player(){

}

void Player::init(SDL_Renderer *renderer){
    player.create(0, 0, width, height, texturePath, "Player", true, true);
    player.setHitboxSizeCentered(22, 47);

    player.getAnim().fps(200);
    player.getAnim().setup("player");
    player.getAnim().setActive(player.getAnim().toTypeFrom("IDLE_UP"));

    if(player.hasDebugMode()){
        cursor.init();
    }

    behavior.init(&player);
    behavior.setPathing(false);
    behavior.setVisionRadius(160 * SCALE);
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
    behavior.updateVision();

    if(player.hasDebugMode()){
        cursor.update();
    }
}


void Player::handleInputKeyboard(){
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

    Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
    if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
        if(timer.elapsedTime() < 1) return;
        timer.start();
        for(Entity* e : behavior.getInRadius()){
            Tile ct = Tile::worldToTile(cursor.getWorldX(), cursor.getWorldY(), e->getWidth());
            Tile et = Tile::worldToTile(e->position.x, e->position.y, e->getWidth());
            if(ct.getTileX() == et.getTileX() && ct.getTileY() == et.getTileY()){
                player.interactWith(Entity::Interaction::ATTACK, e);
            }
        }
    }
}

float Player::getSpeed(){
    return static_cast<float>(player.getAttributes()->getMoveSpeed());
}