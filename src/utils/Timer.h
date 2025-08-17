#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer {

    public:
    Timer();

    int& get();

    void start();
    void show();
    void stop();
    double elapsedTime();

    private:
    int startTime;
    bool isShown;
};

#endif