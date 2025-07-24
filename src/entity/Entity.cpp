#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include "EntityHolder.h"
#include "Animation.h"
#include "../scenes/SceneManager.h"
#include "../Tilemap.h"
#include "../TextureManager.h"
#include "../utils/Text.h"

EntityHolder eHolder;

Entity::Entity(){

}

void Entity::create(float x, float y, const char *pathToTexture, std::string entityName, Relationship r, bool visible, bool collisible, bool animated, bool debugMode){
    width = 32;
    height = 32;
    
    position.x = x;
    position.y = y;
    destRect.w = width;
    destRect.h = height;
    hitbox.w = width;
    hitbox.h = height;

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
}

void Entity::update(SDL_Rect& camera){
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

void Entity::render(SDL_Rect &camera){
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
    eHolder.remove(&e);
    //delete &e;
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
    stats = {200, 200, 150, 55, 0, 0, 0};
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
    return stats[1];
}

int Entity::getMana() const{
    return stats[2];
}

int Entity::getMS() const{
    return stats[3];
}

int Entity::getPDamage() const{
    return stats[4];
}

int Entity::getMDamage() const{
    return stats[5];
}

int Entity::getPRes() const{
    return stats[6];
}

int Entity::getMRes() const{
    return stats[7];
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

EntityHolder::EntityHolder(){
    eHolder.sdlRenderer = nullptr;
}

Entity* EntityHolder::findEntityById(int id){
    for(Entity* entity : eHolder.holder){
        if(entity->getId() == id){
            return entity;
        }
    }
    Logger::print(Logger::ERROR, "Failed to find entity by id");
    return nullptr;
}

int EntityHolder::getIdBy(const Entity* e) const{
    for(Entity* entity : eHolder.holder){
        if(entity == e){
            return entity->getId();
        }
    }
    Logger::print(Logger::ERROR, "Failed to id by entity");
    return -1;
}

std::string EntityHolder::getNameBy(const Entity* e) const{
    for(Entity* entity : eHolder.holder){
        if(entity == e){
            return entity->getName();
        }
    }
    Logger::print(Logger::ERROR, "Failed to find name by entity");
    return "ERROR";
}

void EntityHolder::add(Entity* e){
    eHolder.holder.insert(e);
}

void EntityHolder::remove(Entity* e){
    if(holder.find(e) != eHolder.holder.end()){
        holder.erase(e);
    } else {
        Logger::print(Logger::ERROR, "Failed to remove entity from holder");
    }
}

int EntityHolder::getUniqueId(){
    int uniqueId = 0;

    if(eHolder.holder.empty()){
        return 1;
    }

    for(Entity* entity : eHolder.holder){
        if(entity->getId() > uniqueId){
            uniqueId = entity->getId();
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