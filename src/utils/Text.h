#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include "Logger.h"

class Text {
    public:
    Text();

    void ikuyo(const char *path);
    void render(SDL_Renderer *renderer, const char *message);
    void clear();
    SDL_Texture *create(SDL_Renderer *renderer, const char *message);

    private:
    Logger log;

    TTF_Font *font;
    SDL_Texture *texture;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect = {20, 20, 0, 0};
};

#endif