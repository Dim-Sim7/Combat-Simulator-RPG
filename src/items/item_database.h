#pragma once
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "definitions/weapon_def.h"
#include "definitions/armor_def.h"
#include "definitions/consumable_def.h"
#include "definitions/item_def.h"
//responsible for reading all item definition .csv files and storing in maps

class ItemDatabase {
public:
    ItemDatabase(); //simply calls loadAllItems
    void loadAllItems(); //read from each item database (csv)

    const ItemDef& itemDef(int id) const;
    const WeaponDef& weaponDef(int id) const;
    const ArmorDef& armorDef(int id) const;
    const ConsumableDef& consumableDef(int id) const;

    void printWeapon(const WeaponDef& def) const;

    const std::unordered_map<int, WeaponDef>& weapons() const;

private:
    std::unordered_map<int, ItemDef> baseItems_;
    std::unordered_map<int, WeaponDef> weapons_;
    std::unordered_map<int, ArmorDef> armors_;
    std::unordered_map<int, ConsumableDef> consumables_;


    void loadBaseItems();
    void loadWeapons();
    void loadArmors();
    void loadConsumables();

    ItemType parseItemType(const std::string& str);
    WEAPONTYPE parseWeaponType(const std::string& str);
    ARMORTYPE parseArmorType(const std::string& str);
    ARMORSLOT parseArmorSlot(const std::string& str);
    CONSUMABLETYPE parseConsumableType(const std::string& str);
    std::vector<std::string> splitLine(const std::string& line, char delim = ',');

    
};