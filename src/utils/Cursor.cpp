#include "Cursor.h"
#include "../alg/Vector.h"
#include "../entity/EntityHolder.h"
#include "../Camera.h"
#include <iostream>
#include <SDL2/SDL.h>

Cursor::Cursor(){

}

void Cursor::init(){
    renderer = eHolder.getRenderer();
    text.ikuyo(path);
}

void Cursor::update(){
    SDL_GetMouseState(&screenX, &screenY);
    worldX = screenX + camera.get().x;
    worldY = screenY + camera.get().y;
}

void Cursor::quit(){
    text.quit();
}

int& Cursor::getScreenX(){
    return screenX;
}

int& Cursor::getScreenY(){
    return screenY; 
}

int& Cursor::getWorldX(){
    return worldX;
}

int& Cursor::getWorldY(){
    return worldY;
}