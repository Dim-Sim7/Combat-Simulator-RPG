#pragma once
#include <string>

enum class ItemType {
    Weapon,
    Armor,
    Consumable,
    Misc, //represents quest items, currency, etc...
};

struct ItemDef {
    int id; //used to lookup the corresponding weapon, armor or consumable definition
    std::string name;
    ItemType type;
    bool stackable;
};