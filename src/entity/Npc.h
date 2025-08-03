#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "Behavior.h"
#include "../utils/Tile.h"

class Npc {

    public:
    Npc();

    void spawn(float x, float y, int& w, int& h, const char *pathToTexture, std::string entityName, bool isAnimated, bool debugMode);
    void update();
    void render();
    void kill();

    void addToInventory(Item& item);
    void removeFromInventory(Item& item);

    private:
    Entity npc;
    Behavior behavior;
};

#endif