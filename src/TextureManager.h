#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>

class TextureManager {

    public:
    TextureManager();
    
    static SDL_Texture* load(const char *pathToFIle, SDL_Renderer *renderer);

};

#endif