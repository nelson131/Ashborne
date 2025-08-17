#include "Attributes.h"
#include "Entity.h"
#include <iostream>

Attributes::Attributes(){

}

void Attributes::init(Entity* e){
    this->entity = e;
    this->inv = e->getInventory();
}

const std::array<int, 12> Attributes::getStats(){
    return stats;
}

void Attributes::setDefaultStats(){
    stats = {120, 100, 4, 1, 1, 1, 0, 50, 10, 0, 0, 0};
}

void Attributes::setStats(const std::array<int, 12> s){
    for(int i = 0; i < stats.size(); i++){
        stats[i] = s[i];
    }
}

void Attributes::updateStats(){
    const std::array<int, 10>& invStats = inv->getStats();
    stats[3] += invStats[0]; // Strength
    stats[4] += invStats[1]; // Agility
    stats[5] += invStats[2]; // Intelligence
    stats[6] += invStats[3]; // Armor
    stats[2] += invStats[4]; // Movespeed
    stats[7] += invStats[5]; // Attack speed
    stats[8] += invStats[6]; // Physical damage
    stats[9] += invStats[7]; // Magic damage
    stats[10] += invStats[8]; // Physical resistance
    stats[11] += invStats[9]; // Magical resistance

    // HP
    stats[0] += 22 * stats[3];
    // Mana
    stats[1] += 12 * stats[5];
    // Attack speed
    stats[7] += stats[4];
}