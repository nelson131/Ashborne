#include "Timer.h"
#include "Logger.h"
#include <SDL2/SDL.h>
#include <iomanip>

Timer::Timer(){

}

int& Timer::get(){
    return startTime;
}

void Timer::start(){
    startTime = SDL_GetTicks();
}

void Timer::show(){
    while(isShown){
        Logger::print(Logger::DEBUG, std::fixed, std::setprecision(1), elapsedTime());
    }
}

void Timer::stop(){
    startTime = 0;
}

double Timer::elapsedTime(){
    return (SDL_GetTicks() - startTime) / 1000;
}