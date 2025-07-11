#ifndef ENTITYHOLDER_H
#define ENTITYHOLDER_H

#include "Entity.h"
#include "../utils/Logger.h"
#include <set>

class EntityHolder {

    public:
    EntityHolder();

    void init(SDL_Renderer *renderer);

    Entity* findEntityById(int id);

    int getIdBy(const Entity* e);
    std::string getNameBy(const Entity* e);

    void add(Entity* e);
    void remove(Entity* e);

    SDL_Renderer* getRenderer();

    int getUniqueId();

    private:
    Logger log;

    SDL_Renderer *sdlRenderer;

    std::set<Entity*> holder;
};

extern EntityHolder eHolder;

#endif