#ifndef UI_H
#define UI_H

#include "../alg/Vector.h"
#include <SDL2/SDL.h>
#include <string>

class UI {
    public:
    UI();
    void init();
    void update();
    void render();

    std::string title = "";
    std::string texturePath = "";
    int id = -1;
    bool locked = true;
    bool visible = true;
    SDL_Texture* texture;

    Vector position = {0, 0};
    Vector size = {0, 0};

    private:
    SDL_Rect destRect = {0, 0, 0, 0};
};

#endif