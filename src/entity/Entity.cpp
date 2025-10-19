#include "Entity.h"
#include "EntityHolder.h"
#include "Animation.h"
#include "../alg/Vector.h"
#include "../scenes/SceneManager.h"
#include "../Tilemap.h"
#include "../TextureManager.h"
#include "../utils/Text.h"
#include "../Camera.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <unordered_map>

Entity::Entity(){
    hitboxTexture = nullptr;
}

void Entity::create(const Vector position, const Vector size, const char* pathToTexture, std::string entityName, bool isLiving, bool isAnimated, bool hasDebugMode){
    width = size.x * SCALE;
    height = size.y * SCALE;
    
    this->position.x = position.x;
    this->position.y = position.y;
    
    velocity = {0, 0};
    destRect.w = width;
    destRect.h = height;
    hitbox.w = destRect.w;
    hitbox.h = destRect.h;

    flagName = entityName;
    flagId = eHolder.getUniqueId();
    file = pathToTexture;
    isDebugMode = hasDebugMode;

    setTexture();

    if(hasDebugMode){
        loadHitbox();
        textName.ikuyo("assets/fonts/Roboto-Black.ttf");
        textId.ikuyo("assets/fonts/Roboto-Black.ttf");
        Logger::print(Logger::DEBUG, "Debug mode (", flagName, ") is active");
    }

    if(isAnimated){
        createAnimation();
        animation->setup(flagName);
        animation->setActive(animation->toTypeFrom("IDLE_DOWN"));
    }

    if(isLiving){
        createInventory();
        createAttributes();

        attributes->init(*this);
        attributes->setDefaultStats();
    }

    eHolder.add(this);
}

void Entity::update() {
    handleAnims();
    if(velocity.x != 0 || velocity.y != 0){
        lastDirX = velocity.x;
        lastDirY = velocity.y;
    }

    Vector nextPosition = position;

    nextPosition.x += velocity.x;
    hitbox.x = nextPosition.x + hitboxOffsetX;

    bool collidedX = false;

    for (TilemapLayer& t : sceneManager.getCurrentScene()->colliders) {
        if (hasCollider(t)) {
            collidedX = true;
            break;
        }
    }

    if (!collidedX) {
        for (const auto& [id, entity] : eHolder.get()) {
            if (!entity || entity == this) continue;
            if (hasColliderWith(entity)) {
                collidedX = true;
                break;
            }
        }
    }

    if (!collidedX) {
        position.x = nextPosition.x;
    } else {
        velocity.x = 0;
        hitbox.x = position.x + hitboxOffsetX;
    }

    nextPosition = position;
    nextPosition.y += velocity.y;
    hitbox.y = nextPosition.y + hitboxOffsetY;

    bool collidedY = false;

    for (TilemapLayer& t : sceneManager.getCurrentScene()->colliders) {
        if (hasCollider(t)) {
            collidedY = true;
            break;
        }
    }

    if (!collidedY) {
        for (const auto& [id, entity] : eHolder.get()) {
            if (!entity || entity == this) continue;
            if (hasColliderWith(entity)) {
                collidedY = true;
                break;
            }
        }
    }

    if (!collidedY) {
        position.y = nextPosition.y;
    } else {
        velocity.y = 0;
        hitbox.y = position.y + hitboxOffsetY;
    }
}

void Entity::render(){
    destRect = {
        static_cast<int>(position.x - camera.get().x),
        static_cast<int>(position.y - camera.get().y),
        width,
        height
    };

    if(animation){
        animation->play(srcRect, texture, flip);
    }

    if(!flip) flip = SDL_FLIP_NONE;

    SDL_RenderCopyEx(eHolder.getRenderer(), texture, &srcRect, &destRect, 0.0, nullptr, flip);

    if(isDebugMode){
        destHitbox = {
            static_cast<int>(hitbox.x - camera.get().x),
            static_cast<int>(hitbox.y - camera.get().y),
            hitbox.w,
            hitbox.h
        };

        textName.move(position.x - camera.get().x, position.y - camera.get().y - 40);
        textId.move(position.x - camera.get().x, position.y - camera.get().y - 20);   
        textName.render(eHolder.getRenderer(), flagName.c_str());
        textId.render(eHolder.getRenderer(), std::to_string(flagId).c_str());
        
        SDL_RenderCopy(eHolder.getRenderer(), hitboxTexture, NULL, &destHitbox);
    }
}

void Entity::kill(){
    // pretty bad business ->
    SDL_DestroyTexture(texture);
    eHolder.remove(this);
    delete this;
}

void Entity::snapToTile(Axis axis){
    const int TILE_SIZE = 32 * SCALE;
    switch(axis){
        case Axis::X:
            if(velocity.x > 0){
                position.x = ((int)((hitbox.x + hitbox.w) / TILE_SIZE)) * TILE_SIZE - hitbox.w - 1;
            }
            if(velocity.x < 0){
                position.x = ((int)(hitbox.x / TILE_SIZE) + 1) * TILE_SIZE;
            }
            hitbox.x = position.x;
            break;
        case Axis::Y:
            if(velocity.y > 0){
                position.y = ((int)((hitbox.y + hitbox.h) / TILE_SIZE)) * TILE_SIZE - hitbox.w - 1;
            }
            if(velocity.y < 0){
                position.y = ((int)(hitbox.x / TILE_SIZE) + 1) * TILE_SIZE;
            }
            hitbox.y = position.y;
            break;
    }
}

void Entity::snapToEntity(Axis axis, Entity* e){
    switch(axis){
        case Axis::X:
            if(velocity.x > 0){
                position.x = e->hitbox.x - hitbox.w - 1;
            }
            if(velocity.x < 0){
                position.x = e->hitbox.x + e->hitbox.w + 1;
            }
            hitbox.x = position.x;
            break;
        case Axis::Y:
            if(velocity.y > 0){
                position.y = e->hitbox.y - hitbox.h - 1;
            }
            if(velocity.y < 0){
                position.y = e->hitbox.y + e->hitbox.h + 1;
            }
            hitbox.y = position.y;
    }
}

void Entity::handleAnims(){
    if(!animation) return;

    // Activation idle anims when entity stops ->
    if(velocity.x == 0 && velocity.y == 0){
        if(lastDirX == 0 && lastDirY > 0){
            this->animation->setActive(this->animation->toTypeFrom("IDLE_DOWN"));
            return;
        }
        if(lastDirX == 0 && lastDirY < 0){
            this->animation->setActive(this->animation->toTypeFrom("IDLE_UP"));
            return;
        }
        if(lastDirX > 0){
            this->animation->setActive(this->animation->toTypeFrom("IDLE_RIGHT"));
            return;
        }
        if(lastDirX < 0){
            this->animation->setActive(this->animation->toTypeFrom("IDLE_LEFT"));
            return;
        }
        this->animation->setActive(this->animation->toTypeFrom("IDLE_RIGHT"));
    }

    // Activation run anims when entity moves ->
    if(velocity.x == 0 && velocity.y > 0){
        this->animation->setActive(this->animation->toTypeFrom("RUN_DOWN"));
        return;
    }
    if(velocity.x == 0 && velocity.y < 0){
        this->animation->setActive(this->animation->toTypeFrom("RUN_UP"));
        return;
    }
    if(velocity.x > 0){
        this->animation->setActive(this->animation->toTypeFrom("RUN_RIGHT"));
        return;
    }
    if(velocity.x < 0){
        this->animation->setActive(this->animation->toTypeFrom("RUN_LEFT"));
        return;
    }
}

void Entity::setDebugMode(bool b){
    isDebugMode = b;
}

void Entity::setHitboxSizeCentered(float w, float h){
    hitbox.w = w * SCALE;
    hitbox.h = h * SCALE;
    hitboxOffsetX = (width - w * SCALE) / 2.0f;
    hitboxOffsetY = (height - h * SCALE) / 2.0f;
    
    hitbox.x = position.x + hitboxOffsetX;
    hitbox.y = position.y + hitboxOffsetY;
}

void Entity::setTexture(){
    srcRect = {0, 0, width, height};
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface *surface = IMG_Load(file);
    if(!surface){
        Logger::print(Logger::ERROR, "Failed to load entity surface: ", SDL_GetError());
        return;
    }

    if(!eHolder.getRenderer()){
        Logger::print(Logger::ERROR, "EntityHolder renderer is nullptr");
        return;
    }

    texture = SDL_CreateTextureFromSurface(eHolder.getRenderer(), surface);
    SDL_FreeSurface(surface);
    if(!texture){
        Logger::print(Logger::ERROR, "Failed to load entity texture: ", IMG_GetError());
        return;
    }
}

void Entity::loadHitbox(){
    if(hitboxTexture != nullptr){
        SDL_DestroyTexture(hitboxTexture);
        hitboxTexture = nullptr;
    }
    SDL_Surface* surface = IMG_Load("assets/hitbox.png");
    if(!surface) return;
    if(!eHolder.getRenderer()){
        Logger::print(Logger::ERROR, "Failed to load renderer");
        return;
    }
    hitboxTexture = SDL_CreateTextureFromSurface(eHolder.getRenderer(), surface);
    SDL_FreeSurface(surface);
}

std::string Entity::getName() const{
    return flagName;
}

int Entity::getId() const{
    return flagId;
}

bool Entity::hasDebugMode() const{
    return isDebugMode;
}

void Entity::setWidth(int w){
    width = w;
}

int& Entity::getWidth(){
    return width;
}

void Entity::setHeight(int h){
    height = h;
}

int& Entity::getHeight(){
    return height;
}

void Entity::createAnimation(){
    animation = std::make_unique<Animation>();
}

void Entity::createInventory(){
    inventory = std::make_unique<Inventory>();
}

void Entity::createAttributes(){
    attributes = std::make_unique<Attributes>();
}

Animation* Entity::getAnim(){
    if(animation.get() == nullptr) Logger::print(Logger::ERROR, "Trying to get animation module but anim is nullptr");
    return animation.get();
}

Inventory* Entity::getInventory(){
    if(animation.get() == nullptr) Logger::print(Logger::ERROR, "Trying to get inventory module but inv is nullptr");
    return inventory.get();
}

Attributes* Entity::getAttributes(){
    if(animation.get() == nullptr) Logger::print(Logger::ERROR, "Trying to get attributes module but attr is nullptr");
    return attributes.get();
}

bool Entity::hasCollider(TilemapLayer& t){
    float x1 = hitbox.x;
    float y1 = hitbox.y;
    float x2 = hitbox.x + hitbox.w - 1;
    float y2 = hitbox.y + hitbox.h - 1;

    for(int y = y1; y <= y2; y++){
        for(int x = x1; x <= x2; x++){
            if(t.isBlocked(x, y)){
                return true;
            }
        }
    }
    return false;
}

bool Entity::hasColliderWith(Entity* e){
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = hitbox.x;
    right1 = hitbox.x + hitbox.w;
    top1 = hitbox.y;
    bottom1 = hitbox.y + hitbox.h;

    left2 = e->hitbox.x;
    right2 = e->hitbox.x + e->hitbox.w;
    top2 = e->hitbox.y;
    bottom2 = e->hitbox.y + e->hitbox.h;

    if(bottom1 <= top2 || top1 >= bottom2) return false;
    if(right1 <= left2 || left1 >= right2) return false;

    return true;
}

void Entity::interactWith(Interaction interact, Entity* e2){
    if(attributes->getAttackRange() * SCALE != interactionRange){
        interactionRange = attributes->getAttackRange() * SCALE;
    }
    
    if(this->position.getDistance(e2->position) >= interactionRange){
        Logger::print(Logger::DEBUG, "Not in range");
        return;
    }
    switch(interact){
        case Interaction::ATTACK:
            Logger::print(Logger::DEBUG, "hp before: ", e2->getAttributes()->getHP());
            e2->getAttributes()->getHP() -= (this->attributes->getPhysicalDamage() - (e2->getAttributes()->getArmor() * 0.5) - (e2->getAttributes()->getPhysicalResistance() * 0.3));
            Logger::print(Logger::DEBUG, "hp after: ", e2->getAttributes()->getHP());
            break;
        default:
            break;
    }
}