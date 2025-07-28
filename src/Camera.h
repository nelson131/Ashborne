#ifndef CAMERA_H
#define CAMERA_H

#include "utils/Config.h"
#include <SDL2/SDL.h>

class Camera {

    public:
    Camera();
    
    void update(float& x, float& y, int& w);

    SDL_Rect& get();

    private:
    int sWidth = Config::parse<int>("game_info", "screen_width");
    int sHeight = Config::parse<int>("game_info", "screen_height");
    int cWidth = Config::parse<int>("game_info", "camera_width");
    int cHeight = Config::parse<int>("game_info", "camera_height");
    SDL_Rect camera = {0, 0, cWidth, cHeight};
};

extern Camera camera;

#endif