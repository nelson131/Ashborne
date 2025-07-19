#include "Animation.h"
#include "../utils/Logger.h"
#include <iostream>

Animation::Animation(){

}

void Animation::fps(int fps){
    frameTime = fps;
}

std::map<Animation::Type, int>& Animation::getKeeper(){
    return keeper; 
}

void Animation::add(Animation::Type animType, int cells){
    keeper[animType] = cells;
}

void Animation::remove(Animation::Type animType){
    keeper.erase(animType);
}

void Animation::play(Animation::Type animType, SDL_Rect &srcRect){
    Uint32 now = SDL_GetTicks();

    if(!frameTime || frameTime < 0){
        Logger::print(Logger::ERROR, "Failed to get fps of animation");
    }

    if(now - lastFrameTime > frameTime){
        currentFrame = (currentFrame + 1) % getKeeper()[animType];
        lastFrameTime = now;
    }
    srcRect.x = currentFrame * 32;

    switch (animType)
    {
    case Type::IDLE:
        srcRect.y = 0;
        break;
    case Type::RUNX:
        srcRect.y = 32;
        break;
    case Type::RUNY:
        srcRect.y = 64;
        break;
    default:
        break;
    }

    srcRect.w = 32;
    srcRect.h = 32;
}