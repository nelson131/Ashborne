#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Entity.h"
#include "../utils/Tile.h"
#include <vector>

class Behavior {

    public:
    Behavior();
    enum class Relationship {
        FRIEND,
        NEUTRAL,
        ENEMY,
        PLAYER
    };

    void init(Entity* e);

    Relationship& getRelationship();
    void setRelationship(Relationship r);

    void setPathing(bool b);
    void updatePathing();
    void addDot(Tile t);
    void removeDot(Tile t);
    std::vector<Tile>& getDots();

    void setVisionRadius(float f);
    float getVisionRadius();
    float& getVisionRadiusReal();

    void updateVision();
    void addToRadius(Entity* e);
    void removeFromRadius(Entity* e);
    bool contains(Entity* e);
    std::vector<Entity*>& getInRadius();

    private:
    Entity* entity;
    Relationship rel;

    bool pathing;
    int pathingIndex;
    std::vector<Tile> dots;

    int SCALE = Config::parse<float>("game_info", "scale");
    float visionRadius;
    std::vector<Entity*> inRadius;
};

#endif