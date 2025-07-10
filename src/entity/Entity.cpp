#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include "EntityHolder.h"
#include "../TextureManager.h"

EntityHolder eHolder;

Entity::Entity(){

}

void Entity::create(float x, float y, const char *pathToTexture, std::string entityName, bool visible, bool collisible){
    width = 32;
    height = 32;
    
    position.x = x;
    position.y = y;
    destRect.w = width;
    destRect.h = height;

    flagName = entityName;
    flagId = eHolder.getUniqueId();
    isVisible = visible;
    isCollisible = collisible;

    eHolder.add(this);

    SDL_Surface *surface = IMG_Load(pathToTexture);

    if(!surface){
        log.print(log.ERROR, SDL_GetError());
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(eHolder.getRenderer(), surface);
    SDL_FreeSurface(surface);

}

void Entity::update(){
    position = position + velocity;
    hitBox.x = destRect.x;
    hitBox.y = destRect.y;
    hitBox.w = width;
    hitBox.h = height;
}

void Entity::render(SDL_Rect &camera){
    srcRect = {
        static_cast<int>(position.x - camera.x),
        static_cast<int>(position.y - camera.y),
        width,
        height
    };

    SDL_RenderCopy(eHolder.getRenderer(), texture, NULL, &srcRect);
}

void Entity::kill(Entity& e){
    eHolder.remove(&e);
    //delete &e;
}

void Entity::setVisible(bool &b){
    isVisible = b;
}

void Entity::setCollisible(bool &b){
    isCollisible = b;
}

std::string Entity::getName(){
    return flagName;
}

int Entity::getId(){
    return flagId;
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
    log.print(log.ERROR, "Failed to find entity by id");
    return nullptr;
}

int EntityHolder::getIdBy(const Entity* e){
    for(Entity* entity : eHolder.holder){
        if(entity == e){
            return entity->getId();
        }
    }
    log.print(log.ERROR, "Failed to find id by entity");
    return -1;
}

std::string EntityHolder::getNameBy(const Entity* e){
    for(Entity* entity : eHolder.holder){
        if(entity == e){
            return entity->getName();
        }
    }
    log.print(log.ERROR, "Failed to find name by entity");
    return "ERROR";
}

void EntityHolder::add(Entity* e){
    eHolder.holder.insert(e);
}

void EntityHolder::remove(Entity* e){
    if(holder.find(e) != eHolder.holder.end()){
        holder.erase(e);
    } else {
        log.print(log.ERROR, "Failed to remove entity from holder");
    }
}

int EntityHolder::getUniqueId(){
    int uniqueId = 0;

    if(eHolder.holder.empty()){
        return 1;
    }

    for(Entity* entity : holder){
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
}