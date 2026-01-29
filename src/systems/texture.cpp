#include "texture.hpp"

Texture::Texture() : raw(nullptr), width(0), height(0), path("") {}

Texture::Texture(SDL_Texture* texture, const char* path)
    : path(path), raw(texture) {
    if (raw) {
        SDL_QueryTexture(raw, nullptr, nullptr, &width, &height);
    } else {
        raise_error(ERR_TEXTURE_IS_NULLPTR, path);
    }
}

Texture::~Texture() {
    if (raw) {
        SDL_DestroyTexture(raw);
    }
}

Error Texture::init(SDL_Texture* texture, const char* path) {
    this->raw = texture;
    this->path = path;
    if (raw) {
        SDL_QueryTexture(raw, nullptr, nullptr, &width, &height);
    } else {
        return ERR_TEXTURE_IS_NULLPTR;
    }
    return NONE;
}

SDL_Texture* Texture::get_raw() const { return raw; }

const int& Texture::get_width() const { return width; }

const int& Texture::get_height() const { return height; }

const char* Texture::get_path() const { return path; }
