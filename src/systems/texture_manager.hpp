#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "texture.hpp"

class TextureManager {
   public:
    TextureManager();
    TextureManager(SDL_Renderer* renderer);

    void init(SDL_Renderer* renderer);

    std::shared_ptr<Texture> load(const std::string path);

    void clear();

   private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, std::weak_ptr<Texture>> holder;
};
