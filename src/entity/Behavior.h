#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Entity.h"
#include "Vision.h"
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

    Vision& getVision();

    Relationship& getRelationship();
    void setRelationship(Relationship r);

    // Pathing system funcs ->
    void setPathing(bool b);
    bool& getPathing();
    void updatePathing();
    void addDot(Tile t);
    void removeDot(Tile t);
    std::vector<Tile>& getDots();

    // Pursuit system funcs ->

    private:
    Vision vision;

    Entity* entity;
    Relationship rel;
    int SCALE = Config::parse<float>("game_info", "scale");

    bool pathing = false;
    int pathingIndex = 0;
    std::vector<Tile> dots;
};

#endif