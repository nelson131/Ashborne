#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/error_handler.hpp"

class Texture {
   public:
    Texture();
    Texture(SDL_Texture* texture, const char* path);
    ~Texture();

    Error init(SDL_Texture* texture, const char* path);

    SDL_Texture* get_raw() const;
    const int&   get_width() const;
    const int&   get_height() const;
    const char*  get_path() const;

   private:
    SDL_Texture* raw;
    int          width, height;
    const char*  path;
};
