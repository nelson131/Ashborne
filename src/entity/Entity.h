#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <array>
#include "../alg/Vector.h"
#include "../TextureManager.h"
#include "../item/Inventory.h"
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

    const std::string getName();
    const int getId();
    const bool hasVisible();
    const bool hasCollisible();
    const bool hasDebugMode();

    Inventory inventory;
    
    void setDefaultStats();
    void setStats(const std::array<int, 7> s);
    void updateStats();

    const int getHP();
    const int getMana();
    const int getMS();
    const int getPDamage();
    const int getMDamage();
    const int getPRes();
    const int getMRes();

    Vector position;
    Vector velocity;

    SDL_Rect hitBox;
    SDL_Rect srcRect, destRect;

    private:
    Text textName;
    Text textId;
    SDL_Texture *texture;

    std::string flagName;
    int flagId;
    const char *file;
    bool isVisible, isCollisible, isDebugMode;

    int width, height;

    void setTexture();

    std::array<int, 7> stats;
};

#endif