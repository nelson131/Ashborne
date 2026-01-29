#include "texture_manager.hpp"

#include <iostream>

TextureManager::TextureManager() {}

TextureManager::TextureManager(SDL_Renderer* renderer) : renderer(renderer) {}

void TextureManager::init(SDL_Renderer* renderer) { this->renderer = renderer; }

std::shared_ptr<Texture> TextureManager::load(const std::string path) {
    auto iter = holder.find(path);
    if (iter != holder.end()) {
        auto texture = iter->second.lock();
        return texture;
    }

    SDL_Surface* temp = IMG_Load(path.c_str());
    if (!temp) {
        raise_error(ERR_FAILED_LOAD_SURFACE, path);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture) {
        raise_error(ERR_TEXTURE_IS_NULLPTR, path);
        return nullptr;
    }

    auto shared_texture = std::make_shared<Texture>(texture, path.c_str());
    holder[path] = shared_texture;
    return shared_texture;
}

void TextureManager::clear() { holder.clear(); }
