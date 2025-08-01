#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <unordered_map>
#include "Entity.h"
#include "EntityHolder.h"
#include "Animation.h"
#include "../alg/Vector.h"
#include "../scenes/SceneManager.h"
#include "../Tilemap.h"
#include "../TextureManager.h"
#include "../utils/Text.h"
#include "../Camera.h"

EntityHolder eHolder;

Entity::Entity(){

}

void Entity::create(float x, float y, int& w, int& h, const char *pathToTexture, std::string entityName, bool visible, bool collisible, bool animated, bool debugMode){
    width = w * SCALE;
    height = h * SCALE;
    
    position.x = x;
    position.y = y;
    destRect.w = width;
    destRect.h = height;
    hitbox.w = destRect.w;
    hitbox.h = destRect.h;

    flagName = entityName;
    flagId = eHolder.getUniqueId();
    file = pathToTexture;
    isVisible = visible;
    isCollidable = collisible;
    isAnimated = animated;
    isDebugMode = debugMode;
    
    eHolder.add(this);

    setTexture();

    if(debugMode){
        Logger::print(Logger::DEBUG, "Debug mode (", flagName, ") is active");
        textName.ikuyo("assets/fonts/Roboto-Black.ttf");
        textId.ikuyo("assets/fonts/Roboto-Black.ttf");
    }

    setDefaultStats();
}

void Entity::update() {
    Vector nextPosition = position;

    nextPosition.x += velocity.x;
    hitbox.x = nextPosition.x;

    bool collidedX = false;

    for (TilemapLayer* t : sceneManager.getCurrentScene()->colliders) {
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
        hitbox.x = position.x;
    }

    nextPosition = position;
    nextPosition.y += velocity.y;
    hitbox.y = nextPosition.y;

    bool collidedY = false;

    for (TilemapLayer* t : sceneManager.getCurrentScene()->colliders) {
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
        hitbox.y = position.y;
    }
}

void Entity::render(){
    destRect = {
        static_cast<int>(position.x - camera.get().x),
        static_cast<int>(position.y - camera.get().y),
        width,
        height
    };

    if(isDebugMode){
        textName.move(position.x - camera.get().x, position.y - camera.get().y - 40);
        textId.move(position.x - camera.get().x, position.y - camera.get().y - 20);   
        textName.render(eHolder.getRenderer(), flagName.c_str());
        textId.render(eHolder.getRenderer(), std::to_string(flagId).c_str());
    }
    if(isAnimated){
        animation.play(activeAnim, srcRect);
    }

    SDL_RenderCopy(eHolder.getRenderer(), texture, &srcRect, &destRect);
}

void Entity::kill(Entity& e){
    SDL_DestroyTexture(texture);
    eHolder.remove(&e);
    delete &e;
}

void Entity::snapToTile(Entity::Axis axis){
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
                position.x = ((int)(hitbox.x / TILE_SIZE) + 1) * TILE_SIZE;
            }
            hitbox.x = position.x;
            break;
    }
}

void Entity::snapToEntity(Entity::Axis axis, Entity* e){
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

void Entity::setVisible(bool b){
    isVisible = b;
}

void Entity::setCollisible(bool b){
    isCollidable = b;
}

void Entity::setDebugMode(bool b){
    isDebugMode = b;
}

void Entity::setHitbox(float w, float h){
    hitbox.w = w;
    hitbox.h = h;
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
        exit(1);
    }

    if(!eHolder.getRenderer()){
        Logger::print(Logger::ERROR, "EntityHolder renderer is nullptr");
        exit(-1);
    }

    texture = SDL_CreateTextureFromSurface(eHolder.getRenderer(), surface);
    SDL_FreeSurface(surface);
    if(!texture){
        Logger::print(Logger::ERROR, "Failed to load entity texture: ", IMG_GetError());
        exit(1);
    }
}

std::string Entity::getName() const{
    return flagName;
}

int Entity::getId() const{
    return flagId;
}

bool Entity::hasVisible() const{
    return isVisible;
}

bool Entity::hasCollisible() const{
    return isCollidable;
}

bool Entity::hasDebugMode() const{
    return isDebugMode;
}

int& Entity::getWidth(){
    return width;
}

int& Entity::getHeight(){
    return height;
}

void Entity::setActiveAnim(Animation::Type &type){
    activeAnim = type;
}

void Entity::setDefaultStats(){
    stats = {120, 100, 4, 1, 1, 1, 0, 50, 10, 0, 0, 0};
}

void Entity::setStats(const std::array<int, 12> s){
    for(int i = 0; i < stats.size(); i++){
        stats[i] = s[i];
    }
}

void Entity::updateStats(){
    const std::array<int, 10>& invStats = inventory.getStats();
    stats[3] += invStats[0]; // Strength
    stats[4] += invStats[1]; // Agility
    stats[5] += invStats[2]; // Intelligence
    stats[6] += invStats[3]; // Armor
    stats[2] += invStats[4]; // Movespeed
    stats[7] += invStats[5]; // Attack speed
    stats[8] += invStats[6]; // Physical damage
    stats[9] += invStats[7]; // Magic damage
    stats[10] += invStats[8]; // Physical resistance
    stats[11] += invStats[9]; // Magical resistance

    // HP
    stats[0] += 22 * stats[3];
    // Mana
    stats[1] += 12 * stats[5];
    // Attack speed
    stats[7] += stats[4];
}

int Entity::getHP() const{
    return stats[0];
}

int Entity::getMana() const{
    return stats[1];
}

int Entity::getMoveSpeed() const{
    return stats[2];
}

int Entity::getStrength() const{
    return stats[3];
}

int Entity::getAgility() const{
    return stats[4];
}

int Entity::getIntelligence() const{
    return stats[5];
}

int Entity::getAttackSpeed() const{
    return stats[6];
}

int Entity::getPhysicalDamage() const{
    return stats[7];
}

int Entity::getMagicDamage() const{
    return stats[8];
}

int Entity::getPhysicalResistance() const{
    return stats[9];
}

int Entity::getMagicResistance() const{
    return stats[10];
}

bool Entity::hasCollider(TilemapLayer* t){
    float x1 = hitbox.x;
    float y1 = hitbox.y;
    float x2 = hitbox.x + hitbox.w - 1;
    float y2 = hitbox.y + hitbox.h - 1;

    for(int y = y1; y <= y2; y++){
        for(int x = x1; x <= x2; x++){
            if(t->isBlocked(x, y)){
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

EntityHolder::EntityHolder(){
    eHolder.sdlRenderer = nullptr;
}

std::unordered_map<int, Entity*>& EntityHolder::get(){
    return eHolder.holder;
}

Entity* EntityHolder::findEntityById(int id){
    if(eHolder.get().count(id)){
        return eHolder.get()[id];
    }
    Logger::print(Logger::ERROR, "Failed to find entity by id");
    return nullptr;
}

int EntityHolder::getIdBy(const Entity* e) const{
    for(const auto& [id, entity] : eHolder.holder){
        if(entity == e){
            return id;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find id by entity");
    return -1;
}

std::string EntityHolder::getNameBy(const Entity* e) const{
    for(const auto& [id, entity] : eHolder.holder){
        if(entity && entity->getName() == e->getName()){
            return entity->getName();
        }
    }
    Logger::print(Logger::ERROR, "Failed to find name by entity");
    return "ERROR";
}

void EntityHolder::add(Entity* e){
    eHolder.get()[e->getId()] = e;
}

void EntityHolder::remove(Entity* e){
    int id = getIdBy(e);
    if(id == -1){
        Logger::print(Logger::ERROR, "Failed to ыfind entity in remove func");
        return;
    }
    eHolder.get().erase(id);
}

int EntityHolder::getUniqueId(){
    int uniqueId = 0;

    if(eHolder.holder.empty()){
        return 1;
    }

    for(const auto& [id, Entity] : eHolder.get()){
        if(id > uniqueId){
            uniqueId = id;
        }
    }
    return uniqueId + 1;
}

SDL_Renderer* EntityHolder::getRenderer(){
    return eHolder.sdlRenderer;   
}

void EntityHolder::init(SDL_Renderer *renderer){
    eHolder.sdlRenderer = renderer;
    Logger::print(Logger::SUCCESS, "Entity holder initialized");
}

bool EntityHolder::inRange(const Entity* e1, const Entity* e2){
    return e1->position.getDistance(e2->position) <= avr;
}