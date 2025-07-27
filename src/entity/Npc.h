#ifndef NPC_H
#define NPC_H

#include "Entity.h"

class Npc {

    public:
    Npc();

    void spawn(float x, float y, const char *pathToTexture, std::string entityName, Entity::Relationship relationship, bool isVisible, bool isCollisible, bool isAnimated, bool debugMode);
    void update();
    void render();
    void kill();

    void addToInventory(Item& item);
    void removeFromInventory(Item& item);

    bool scanTargets();
    bool inView();

    private:
    Entity npc;
};

#endif