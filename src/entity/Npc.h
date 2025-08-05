#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "Behavior.h"
#include "../utils/Tile.h"
#include "../utils/Config.h"

class Npc {

    public:
    Npc();

    void spawn();
    void update();
    void render();
    void kill();

    void setSpawnPars(float& x, float& y, int& w, int& h, std::string path, std::string& n, bool& isAnimated, bool& debugMode);

    Entity& getEntity();
    Behavior& getBehavior();

    void setBehavior(bool p, float visionRadius);
    void addDots(std::vector<Vector> d);

    void addToInventory(Item& item);
    void removeFromInventory(Item& item);

    bool operator<(Npc& other) const {
        return this->npc.getId() < other.npc.getId();
    }

    private:
    Entity npc;
    Behavior behavior;

    int SCALE = Config::parse<float>("game_info", "scale");

    float spawnX, spawnY;
    int width, height;
    std::string path, name;
    bool animated, debugmode;
};

#endif