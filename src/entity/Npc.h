#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "../utils/Tile.h"

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

    std::vector<Tile>& getDots();
    void addDot(Tile t);
    void removeDot(Tile t);

    void setPathing(bool b);
    bool& getPathing();

    private:
    Entity npc;

    int index = 0;

    bool pathing;
    std::vector<Tile> dots;

};

#endif