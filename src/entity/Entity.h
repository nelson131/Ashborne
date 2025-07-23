#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <array>
#include "Animation.h"
#include "../Tilemap.h"
#include "../alg/Vector.h"
#include "../TextureManager.h"
#include "../item/Inventory.h"
#include "../utils/Text.h"

class Entity {

    public:
    Entity();

    enum class Relationship {
        FRIENDLY,
        ENEMY,
        NEUTRAL,
        PLAYER
    };

    void create(float x, float y, const char *pathToTexture, std::string entityName, Relationship relationship, bool isVisible, bool isCollisible, bool isAnimated, bool debugMode);
    void update(SDL_Rect& camera);
    void render(SDL_Rect& camera);
    void kill(Entity& e);

    Relationship& getRelationship();
    void setRelationship(Relationship &rel);

    void setVisible(bool b);
    void setCollisible(bool b);
    void setDebugMode(bool b);

    std::string getName() const;
    int getId() const;
    bool hasVisible() const;
    bool hasCollisible() const;
    bool hasDebugMode() const;

    Animation animation;

    void setActiveAnim(Animation::Type &type);

    Inventory inventory;

    void setDefaultStats();
    void setStats(const std::array<int, 7> s);
    void updateStats();

    int getHP() const;
    int getMana() const;
    int getMS() const;
    int getPDamage() const;
    int getMDamage() const;
    int getPRes() const;
    int getMRes() const;

    bool hasCollider(TilemapLayer* t);

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
    Relationship rel;
    bool isVisible, isCollidable, isDebugMode, isAnimated;

    int width, height;

    void setTexture();

    std::array<int, 7> stats;

    Animation::Type activeAnim;
};

#endif