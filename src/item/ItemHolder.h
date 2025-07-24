#ifndef ITEMHOLDER_H
#define ITEMHOLDER_H

#include <array>
#include <set>

/*
    parameters meanings:
    1. HP
    2. Mana
    3. Movespeed
    4. Phys damage
    5. Magic damage
    6. Phys res
    7. Magic res
*/

struct Item
{
    const char *name;
    int id;
    std::array<int, 7> parameters;
    bool isEquipable;

    bool operator==(const Item& other) const {
        return parameters == other.parameters;
    }
};

class ItemHolder {

    public:
    ItemHolder();

    void init();

    std::set<const Item*>& get() const;
    const Item* findBy(const char* name) const;
    const Item* findBy(int id) const;

    void add(const Item *item);
    void remove(const Item *item);

    private:
    int getUniqueId();

    std::set<const Item*> holder;
};

extern ItemHolder itemHolder;

#endif