#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <array>
#include "../alg/Vector.h"
#include "../TextureManager.h"
#include "../utils/Text.h"

class Entity {

    public:
    Entity();

    void create(float x, float y, const char *pathToTexture, std::string entityName, bool isVisible, bool isCollisible, bool debugMode);
    void update();
    void render(SDL_Rect& camera);
    void kill(Entity& e);

    void setVisible(bool b);
    void setCollisible(bool b);
    void setDebugMode(bool b);
    void setTexture(const char *pathToTexture);

    std::string getName();
    int getId();

    Vector position;
    Vector velocity;

    SDL_Rect hitBox;
    SDL_Rect srcRect, destRect;

    private:
    Logger log;
    Text textName;
    Text textId;
    SDL_Texture *texture;

    std::string flagName;
    int flagId;

    bool isVisible, isCollisible, isDebugMode;

    int width, height;
};

#endif