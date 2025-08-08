#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer {

    public:
    Timer();

    int& get();

    void start();
    int elapsedTime();
    void stop();

    private:
    int startTime;
};

#endif