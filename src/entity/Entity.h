#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <array>
#include "../alg/Vector.h"
#include "../TextureManager.h"

class Entity {

    public:
    Entity();

    void create(float x, float y, const char *pathToTexture, std::string entityName, bool isVisible, bool isCollisible);
    void update();
    void render(SDL_Rect& camera);
    void kill(Entity& e);

    void setVisible(bool &b);
    void setCollisible(bool &b);

    std::string getName();
    int getId();

    Vector position;
    Vector velocity;

    SDL_Rect hitBox;
    SDL_Rect srcRect, destRect;

    private:
    SDL_Texture *texture;
    Logger log;

    std::string flagName;
    int flagId;

    bool isVisible, isCollisible;

    int width, height;
};

#endif