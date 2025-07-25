#include "Cursor.h"
#include "../alg/Vector.h"
#include "../entity/EntityHolder.h"
#include <iostream>
#include <SDL2/SDL.h>

Cursor::Cursor(){

}

void Cursor::init(){
    renderer = eHolder.getRenderer();
    text.ikuyo(path);
}

void Cursor::update(){
    SDL_GetMouseState(&mouseX, &mouseY);
}

void Cursor::quit(){
    text.quit();
}

int& Cursor::getX(){
    return mouseX;
}

int& Cursor::getY(){
    return mouseY;
}