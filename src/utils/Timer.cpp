#include "Timer.h"
#include <SDL2/SDL.h>

Timer::Timer(){

}

int& Timer::get(){
    return startTime;
}

void Timer::start(){
    startTime = SDL_GetTicks();
}

int Timer::elapsedTime(){
    return (SDL_GetTicks() - startTime) / 1000;
}

void Timer::stop(){
    startTime = 0;
}