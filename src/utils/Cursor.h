#ifndef CURSOR_H
#define CURSOR_H

#include "../alg/Vector.h"
#include "Text.h"
#include <sstream>

class Cursor {

    public:
    Cursor();

    void init();
    void update();
    void quit();

    int& getX();
    int& getY();

    template<typename... Targs>
    void render(const Targs&... args){
        std::ostringstream str;
        (str << ... << args);
        text.render(renderer, str.str().c_str());
        text.move(getX()-20, getY()-20);
        text.clear();
    }

    Vector position;

    private:
    Text text;

    SDL_Renderer* renderer;

    const char *path = "assets/fonts/Roboto-Black.ttf";
    int mouseX, mouseY;
};

#endif