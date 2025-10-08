#ifndef UIMODULE_H
#define UIMODULE_H

#include "../entity/EntityHolder.h"
#include "../alg/Vector.h"
#include <SDL2/SDL.h>
#include <string>

namespace UIModule {

    struct Base {
        SDL_Renderer* renderer = eHolder.getRenderer(); 

        Vector local = {0, 0};
        Vector global = {0, 0};
        SDL_Rect destRect = {0, 0, 0, 0};
        SDL_Rect srcRect = {0, 0, 0, 0};

        virtual void init(const Vector v, int width, int height);
        virtual void update(Vector& relative);
        virtual void render();
    };

    struct Image : public Base {
        std::string texturePath = ""; 
        SDL_Texture *texture = nullptr;

        void init(const Vector v, int width, int height) override {
            this->local = v;
            destRect.w = width;
            srcRect.w = width;
            destRect.h = height;
            srcRect.h = height;
        }

        void update(Vector& relative) override {
            global.x = relative.x + local.x;
            global.y = relative.y + local.y;
        }

        void render() override {
            SDL_RenderCopy(this->renderer, texture, &srcRect, &destRect);
        }

        void load(){
            if(texture != nullptr){
                SDL_DestroyTexture(texture);
            }
            texture = TextureManager::load(texturePath.c_str(), this->renderer);
        }
    };
};

#endif