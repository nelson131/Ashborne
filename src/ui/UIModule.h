#ifndef UIMODULE_H
#define UIMODULE_H

#include "../entity/EntityHolder.h"
#include "../alg/Vector.h"
#include "../utils/Logger.h"
#include "../utils/Text.h"
#include <SDL2/SDL.h>
#include <string>

namespace UIModule {

    struct Base {
        SDL_Renderer* renderer = eHolder.getRenderer(); 

        Vector local = {0, 0};
        Vector global = {0, 0};
        SDL_Rect destRect = {0, 0, 0, 0};
        SDL_Rect srcRect = {0, 0, 0, 0};

        virtual void init(const Vector v, const Vector size);
        virtual void update(Vector& relative);
        virtual void render();
    };

    struct Image : public Base {
        std::string texturePath = ""; 
        SDL_Texture *texture = nullptr;

        void init(const Vector v, const Vector size) override {
            this->local = v;
            destRect.w = size.x;
            srcRect.w = destRect.w;
            destRect.h = size.y;
            srcRect.h = destRect.h;
        }

        void update(Vector& relative) override {
            global.x = relative.x + local.x;
            global.y = relative.y - local.y;
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

    struct Message : public Base {
        Text text;
        std::string content = "";
        std::string font = "";

        void init(const Vector v, const Vector size) override {
            this->local = v;
            destRect.w = size.x;
            srcRect.w = destRect.w;
            destRect.h = size.y;
            srcRect.h = destRect.h;

            if(font.empty()){
                Logger::print(Logger::ERROR, "Failed to load textUI cause font is empty");
                return;
            }
            text.ikuyo(font.c_str());
        }

        void update(Vector& relative) override {
            global.x = relative.x + local.x;
            global.y = relative.y - local.y;
            text.put(global);
        }

        void render() override {
            if(content.empty()) return;
            text.render(this->renderer, content.c_str());
        }
    };
};

#endif