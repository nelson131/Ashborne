#ifndef ENTITYHOLDER_H
#define ENTITYHOLDER_H

#include "Entity.h"
#include "../utils/Logger.h"
#include "../utils/Config.h"
#include <unordered_map>

class EntityHolder {

    public:
    EntityHolder();

    void init(SDL_Renderer *renderer);

    std::unordered_map<int, Entity*>& get();

    Entity* findEntityById(int id);
    int getIdBy(const Entity* e) const;
    std::string getNameBy(const Entity* e) const;

    void add(Entity* e);
    void remove(Entity* e);

    bool inRange(const Entity* e1, const Entity* e2);

    SDL_Renderer* getRenderer();

    int getUniqueId();

    private:
    SDL_Renderer *sdlRenderer;
    std::unordered_map<int, Entity*> holder;

    int avr = Config::parse<float>("npc_info", "absolute_view_range");
};

extern EntityHolder eHolder;

#endif