#ifndef UI_H
#define UI_H

#include "UIModule.h"
#include "../alg/Vector.h"
#include <SDL2/SDL.h>
#include <string>

struct Container {
    std::vector<UIModule::Image> images;
};

class UI {
    public:
    UI();
    void init();
    void update();
    void render();

    std::string title = "";
    int id = -1;
    bool locked = true;
    bool visible = true;

    Vector position = {0, 0};

    Container container;

    private:
    SDL_Rect destRect = {0, 0, 0, 0};
};

#endif