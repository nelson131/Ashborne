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
#include "../Camera.h"

class Entity {

    public:
    Entity();

    void create(float x, float y, int& w, int& h, const char *pathToTexture, std::string entityName, bool isVisible, bool isCollisible, bool isAnimated, bool debugMode);
    void update();
    void render();
    void kill(Entity& e);

    void setVisible(bool b);
    void setCollisible(bool b);
    void setDebugMode(bool b);

    void setHitbox(float w, float h);

    std::string getName() const;
    int getId() const;
    bool hasVisible() const;
    bool hasCollisible() const;
    bool hasDebugMode() const;

    int& getWidth();
    int& getHeight();

    Animation animation;

    void setActiveAnim(Animation::Type &type);

    Inventory inventory;

    void setDefaultStats();
    void setStats(const std::array<int, 12> s);
    void updateStats();

    int getHP() const;
    int getMana() const;
    int getMoveSpeed() const;
    int getStrength() const;
    int getAgility() const;
    int getIntelligence() const;
    int getAttackSpeed() const;
    int getPhysicalDamage() const;
    int getMagicDamage() const;
    int getPhysicalResistance() const;
    int getMagicResistance() const;

    bool hasCollider(TilemapLayer* t);
    bool hasColliderWith(Entity* e);

    Vector position;
    Vector velocity;

    SDL_Rect hitbox;
    SDL_Rect srcRect, destRect;

    private:
    Text textName;
    Text textId;
    SDL_Texture *texture;
    int SCALE = Config::parse<float>("game_info", "scale");

    std::string flagName;
    int flagId;
    const char *file;
    bool isVisible, isCollidable, isDebugMode, isAnimated;

    int width, height;

    void setTexture();

    enum class Axis {
        X, Y
    };

    void snapToTile(Axis axis);
    void snapToEntity(Axis axis, Entity* e);

    std::array<int, 12> stats;

    Animation::Type activeAnim;

    float cr = Config::parse<float>("entity_info", "collision_range");
};

#endif