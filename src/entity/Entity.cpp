#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include "EntityHolder.h"
#include "Animation.h"
#include "../TextureManager.h"
#include "../utils/Text.h"

EntityHolder eHolder;

Entity::Entity(){

}

void Entity::create(float x, float y, const char *pathToTexture, std::string entityName, bool visible, bool collisible, bool animated, bool debugMode){
    width = 32;
    height = 32;
    
    position.x = x;
    position.y = y;
    destRect.w = width;
    destRect.h = height;
    hitBox.w = width;
    hitBox.h = height;

    flagName = entityName;
    flagId = eHolder.getUniqueId();
    file = pathToTexture;
    isVisible = visible;
    isCollisible = collisible;
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

void Entity::update(){
    position = position + velocity;
    hitBox.x = position.x;
    hitBox.y = position.y;

    textName.move(position.x, position.y - 40);
    textId.move(position.x, position.y - 20);
}

void Entity::render(SDL_Rect &camera){
    destRect = {
        static_cast<int>(position.x - camera.x),
        static_cast<int>(position.y - camera.y),
        width,
        height
    };

    if(isDebugMode){
        //SDL_SetRenderDrawColor(eHolder.getRenderer(), 41, 182, 246, 255);
        //SDL_RenderDrawRect(eHolder.getRenderer(), &hitBox);
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

void Entity::setVisible(bool b){
    isVisible = b;
}

void Entity::setCollisible(bool b){
    isCollisible = b;
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
    return isCollisible;
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