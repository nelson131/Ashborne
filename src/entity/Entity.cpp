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

EntityHolder eHolder;

Entity::Entity(){

}

void Entity::create(float x, float y, const char *pathToTexture, std::string entityName, Relationship r, bool visible, bool collisible, bool animated, bool debugMode){
    width = 32 * SCALE;
    height = 32 * SCALE;
    
    position.x = x;
    position.y = y;
    destRect.w = width;
    destRect.h = height;
    hitbox.w = destRect.w;
    hitbox.h = destRect.h;

    flagName = entityName;
    flagId = eHolder.getUniqueId();
    file = pathToTexture;
    rel = r;
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

void Entity::update(){
   position.x += velocity.x;
   hitbox.x = position.x;

   for(TilemapLayer* t : sceneManager.getCurrentScene()->colliders){
        if(hasCollider(t)){
            if(velocity.x > 0){
                position.x = (int)(position.x / 32) * 32;
            }
            if(velocity.x < 0){
                position.x = (int)(position.x / 32 + 1) * 32;
            }
            hitbox.x = position.x;
            break;
        }
   }

   position.y += velocity.y;
   hitbox.y = position.y;

   for(TilemapLayer* t : sceneManager.getCurrentScene()->colliders){
        if(hasCollider(t)){
            if(velocity.y > 0){
                position.y = (int)(position.y / 32) * 32;
            }
            if(velocity.y < 0){
                position.y = (int)(position.y / 32 + 1) * 32;
            }
            hitbox.y = position.y;
            break;
        }
   }

   textName.move(position.x - camera.x, position.y - 40 - camera.y);
   textId.move(position.x - camera.x, position.y - 20 - camera.y);
}

void Entity::render(){
    destRect = {
        static_cast<int>(position.x - camera.x),
        static_cast<int>(position.y - camera.y),
        width,
        height
    };

    if(isDebugMode){
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

Entity::Relationship& Entity::getRelationship(){
    return rel;
}

void Entity::setRelationship(Entity::Relationship &r){
    rel = r;
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

void Entity::updateCamera(SDL_Rect& c){
    camera = c;
}

void Entity::setTexture(){
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

void Entity::setActiveAnim(Animation::Type &type){
    activeAnim = type;
}

void Entity::setDefaultStats(){
    stats = {300, 200, 4, 10, 0, 0, 0};
}

void Entity::setStats(const std::array<int, 7> s){
    for(int i = 0; i < stats.size(); i++){
        stats[i] = s[i];
    }
}

void Entity::updateStats(){
    for(int i = 0; i < stats.size(); i++){
        stats[i] += inventory.getStats()[i];
    }
}

int Entity::getHP() const{
    return stats[0];
}

int Entity::getMana() const{
    return stats[1];
}

int Entity::getMS() const{
    return stats[2];
}

int Entity::getPDamage() const{
    return stats[3];
}

int Entity::getMDamage() const{
    return stats[4];
}

int Entity::getPRes() const{
    return stats[5];
}

int Entity::getMRes() const{
    return stats[6];
}

bool Entity::hasCollider(TilemapLayer* t){
    float x1 = hitbox.x;
    float y1 = hitbox.y;
    float x2 = hitbox.x + hitbox.w - 1;
    float y2 = hitbox.y + hitbox.h - 1;

    return t->isBlocked(x1, y1)
        || t->isBlocked(x2, y2)
        || t->isBlocked(x1, y2)
        || t->isBlocked(x2, y1);
}

void Entity::setFOV(float f){
    fov = f;
}

bool Entity::inView(Entity* e){
    
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
    for(size_t i = 0; i < eHolder.get().size(); i++){
        if(eHolder.get()[i] == e){
            return static_cast<int>(i);
        }
    }
    Logger::print(Logger::ERROR, "Failed to id by entity");
    return -1;
}

std::string EntityHolder::getNameBy(const Entity* e) const{
    for(size_t i = 0; i < eHolder.get().size(); i++){
        if(eHolder.get()[i]->getName() == e->getName()){
            return eHolder.get()[i]->getName();
        }
    }
    Logger::print(Logger::ERROR, "Failed to find name by entity");
    return "ERROR";
}

void EntityHolder::add(Entity* e){
    eHolder.get()[getUniqueId()] = e;
}

void EntityHolder::remove(Entity* e){
    int id = getIdBy(e);
    if(id == -1){
        Logger::print(Logger::ERROR, "Failed to find entity in remove func");
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