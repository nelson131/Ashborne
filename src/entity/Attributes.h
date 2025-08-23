#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../item/Inventory.h"
#include <array>

class Entity;

class Attributes {
    public:
    Attributes();
    void init(Entity& e);

    const std::array<int, 12>& getStats();
    void setDefaultStats();
    void setStats(const std::array<int, 12> s);
    void updateStats();

    int& getHP() { return stats[0]; }
    int& getMana() { return stats[1]; }
    int& getMoveSpeed() { return stats[2]; }
    int& getStrength() { return stats[3]; }
    int& getAgility() { return stats[4]; }
    int& getIntelligence() { return stats[5]; }
    int& getArmor() { return stats[6]; }
    int& getAttackSpeed() { return stats[7]; }
    int& getPhysicalDamage() { return stats[8]; }
    int& getMagicDamage() { return stats[9]; }
    int& getPhysicalResistance() { return stats[10]; }
    int& getMagicResistance() { return stats[11]; }

    private:
    Entity* entity;
    Inventory* inv;

    std::array<int, 12> stats;
};

#endif