#ifndef ITEMHOLDER_H
#define ITEMHOLDER_H

#include <iostream>
#include <array>
#include <set>
#include <memory>

struct Item
{
    std::string name;
    std::string desc;
    int id;
    std::array<int, 11> parameters;
    bool isEquipable;

    bool operator==(const Item& other) const {
        return parameters == other.parameters;
    }

    bool operator<(const Item& other) const {
    return this->id < other.id;
    }
};

class ItemHolder {

    public:
    ItemHolder();

    void init();

    std::set<Item>& get() const;
    const Item& findBy(const char* name) const;
    const Item& findBy(int id) const;

    void add(const Item item);
    void remove(const Item &item);

    int getUniqueId();

    private:
    std::set<Item> holder;

    const char *path = "resources/items.ini";
};

extern ItemHolder itemHolder;

#endif