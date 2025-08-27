#ifndef VISION_H
#define VISION_H

#include "Entity.h"
#include "../utils/Config.h"
#include <vector>

class Vision {
    public:
    Vision();

    void init(Entity*& e);
    void update();

    float getRange();
    float& getRangeReal();
    void setRange(float r);

    void add(Entity* e);
    void remove(Entity* e);
    bool contains(Entity* e);
    std::vector<Entity*>& getInRange();

    private:
    Entity* self;

    float range;
    std::vector<Entity*> inRange;
    int SCALE = Config::parse<float>("game_info", "scale");
};

#endif