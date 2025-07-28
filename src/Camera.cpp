#include "Camera.h"
#include <iostream>
#include <SDL2/SDL.h>

Camera camera;

Camera::Camera(){

}

void Camera::update(float& x, float& y, int& w){
    camera.x = (x + w / 2) - sWidth / 2;
    camera.y = (y + w / 2) - sHeight / 2;
}

SDL_Rect& Camera::get(){
    return camera;
}