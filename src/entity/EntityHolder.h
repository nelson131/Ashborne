#ifndef ENTITYHOLDER_H
#define ENTITYHOLDER_H

#include "Entity.h"
#include "../utils/Logger.h"
#include <set>

extern EntityHolder entityHolder;

class EntityHolder {

    public:
    EntityHolder();
    Entity* findEntityById(int id);

    int getIdBy(const Entity* e);
    std::string getNameBy(const Entity* e);

    void add(Entity* e);
    void remove(Entity* e);

    int getUniqueId();

    private:
    Logger log;

    std::set<Entity*> holder;
};

#endif