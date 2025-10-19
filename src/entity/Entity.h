#ifndef ENTITY_H
#define ENTITY_H

#include "Animation.h"
#include "Attributes.h"
#include "../Tilemap.h"
#include "../alg/Vector.h"
#include "../TextureManager.h"
#include "../item/Inventory.h"
#include "../utils/Text.h"
#include "../Camera.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <array>

enum class Axis {
    X, Y
};

class Entity {

    public:
    Entity();

    void create(const Vector position, const Vector size, const char* pathToTexture, std::string entityName, bool isLiving, bool isAnimated, bool debugMode);
    void update();
    void render();
    void kill();

    void setDebugMode(bool b);

    void setHitboxSizeCentered(float w, float h);

    std::string getName() const;
    int getId() const;
    bool hasDebugMode() const;

    void setWidth(int w);
    int& getWidth();

    void setHeight(int h);
    int& getHeight();

    Animation* getAnim();
    Inventory* getInventory();
    Attributes* getAttributes();

    bool hasCollider(TilemapLayer& t);
    bool hasColliderWith(Entity* e);

    enum class Interaction {
        ATTACK,
        DIALOG
    };

    void interactWith(Interaction interact, Entity* e);

    Vector position;
    Vector velocity;

    SDL_Rect destHitbox, hitbox;
    SDL_Rect srcRect, destRect;

    private:
    std::shared_ptr<Inventory> inventory;
    std::shared_ptr<Animation> animation;
    std::shared_ptr<Attributes> attributes;

    void createAnimation();
    void createInventory();
    void createAttributes();

    Text textName;
    Text textId;
    SDL_Texture *texture;
    SDL_Texture *hitboxTexture;
    SDL_RendererFlip flip;
    int SCALE = Config::parse<float>("game_info", "scale");

    std::string flagName;
    int flagId;
    const char*  file;
    bool isDebugMode;

    int width, height;

    void setTexture();
    void loadHitbox();

    float hitboxOffsetX = 0;
    float hitboxOffsetY = 0;

    void snapToTile(Axis axis);
    void snapToEntity(Axis axis, Entity* e);

    void handleAnims();
    int lastDirX = 0;
    int lastDirY = 0;

    std::array<int, 12> stats;

    float cr = Config::parse<float>("entity_info", "collision_range");

    float interactionRange = 120;
};

#endif