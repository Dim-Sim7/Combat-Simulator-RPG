#include "item_database.h"


ItemDatabase::ItemDatabase() {
    loadAllItems();
} 
void ItemDatabase::loadAllItems() {
    loadBaseItems();
    loadArmors();
    loadWeapons();
    loadConsumables();
}

const std::unordered_map<int, WeaponDef>& ItemDatabase::weapons() const {
    return weapons_;
}

const ItemDef& ItemDatabase::itemDef(int id) const {
    return baseItems_.at(id);
}

const WeaponDef& ItemDatabase::weaponDef(int id) const {
    return weapons_.at(id);
}

const ArmorDef& ItemDatabase::armorDef(int id) const {
    return armors_.at(id);
}

const ConsumableDef& ItemDatabase::consumableDef(int id) const {
    return consumables_.at(id);
}

void ItemDatabase::loadWeapons() {
    std::ifstream file("src/items/data/weapon_table.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitLine(line);
        if (fields.size() < 5) continue;

        WeaponDef def {
            std::stoi(fields[0]),
            std::stoi(fields[1]),
            std::stoi(fields[2]),
            std::stof(fields[3]),
            parseWeaponType(fields[4])
        };
        weapons_.emplace(def.weapon_id, def);
        
    }

}

void ItemDatabase::loadArmors() {
    std::ifstream file("src/items/data/armor_table.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitLine(line);
        if (fields.size() < 5) continue;
        std::string type = fields[4];
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        std::string slot = fields[5];
        std::transform(slot.begin(), slot.end(), slot.begin(), ::toupper);
        ArmorDef def {
            std::stoi(fields[0]),
            std::stoi(fields[1]),
            std::stoi(fields[2]),
            parseArmorType(type),
            parseArmorSlot(slot)
        };

        armors_.emplace(def.armor_id, def);
    }

}

void ItemDatabase::loadConsumables() {
    std::ifstream file("src/items/data/consumable_table.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitLine(line);

        if (fields.size() < 10) continue;

        StatModifier mod;
        int dmgMin = std::stoi(fields[4]);
        int dmgMax = std::stoi(fields[5]);
        if (dmgMin != 0 || dmgMax != 0)
            mod.damage = { dmgMin, dmgMax };
        
        int armor = std::stoi(fields[6]);
        if (armor != 0)
            mod.armor = armor;
        
        float speed = std::stof(fields[7]);
        if (speed != 0.0) 
            mod.speed = speed;
        
        int health = std::stoi(fields[8]);
        if (health != 0)
            mod.health = health;

        bool isStackable = (fields[2] == "true");
        ConsumableDef def {
            std::stoi(fields[0]),
            std::stoi(fields[1]),
            isStackable,
            std::stof(fields[3]),
            mod,
            parseConsumableType(fields[9])
        };

        consumables_.emplace(def.consumable_id, def);
    }
}


void ItemDatabase::loadBaseItems() {
    std::ifstream file("src/items/data/base_item_table.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        char firstChar;
        ss >> firstChar;

        if (!line.empty() || (firstChar != '#')) {
            auto fields = splitLine(line);
            if (fields.size() < 4)
                continue;

            ItemDef def{
                std::stoi(fields[0]),
                fields[1],
                parseItemType(fields[2]),
                (fields[3] == "true")
            };

            baseItems_.emplace(def.id, def);

        }
    }
}

ItemType ItemDatabase::parseItemType(const std::string& str) {
    if (str == "Weapon")           return ItemType::Weapon;
    if (str == "Armor")            return ItemType::Armor;
    if (str == "Consumable")       return ItemType::Consumable;

    throw std::runtime_error("Unknown ItemType: " + str);
}

WEAPONTYPE ItemDatabase::parseWeaponType(const std::string& str) {
    if (str == "DAGGER")          return WEAPONTYPE::DAGGER;
    if (str == "FIST_WEAPON")     return WEAPONTYPE::FIST_WEAPON;
    if (str == "ONE_HAND_AXE")    return WEAPONTYPE::ONE_HAND_AXE;
    if (str == "ONE_HAND_MACE")   return WEAPONTYPE::ONE_HAND_MACE;
    if (str == "ONE_HAND_SWORD")  return WEAPONTYPE::ONE_HAND_SWORD;
    if (str == "POLEARM")         return WEAPONTYPE::POLEARM;
    if (str == "STAVE")           return WEAPONTYPE::STAVE;
    if (str == "TWO_HAND_AXE")    return WEAPONTYPE::TWO_HAND_AXE;
    if (str == "TWO_HAND_MACE")   return WEAPONTYPE::TWO_HAND_MACE;
    if (str == "TWO_HAND_SWORD")  return WEAPONTYPE::TWO_HAND_SWORD;
    if (str == "BOW")             return WEAPONTYPE::BOW;
    if (str == "CROSSBOW")        return WEAPONTYPE::CROSSBOW;
    if (str == "GUN")             return WEAPONTYPE::GUN;
    if (str == "THROWN")          return WEAPONTYPE::THROWN;
    if (str == "WAND")            return WEAPONTYPE::WAND;

    throw std::runtime_error("Unknown WEAPONTYPE: " + str);
}


ARMORTYPE ItemDatabase::parseArmorType(const std::string& str) {
    if (str == "CLOTH")           return ARMORTYPE::CLOTH;
    if (str == "LEATHER")         return ARMORTYPE::LEATHER;
    if (str == "MAIL")            return ARMORTYPE::MAIL;
    if (str == "PLATE")           return ARMORTYPE::PLATE;

    throw std::runtime_error("Unknown ARMORTYPE: " + str);
}

ARMORSLOT ItemDatabase::parseArmorSlot(const std::string& str) {
    if (str == "CHEST")     return ARMORSLOT::CHEST;
    if (str == "FEET")      return ARMORSLOT::FEET;
    if (str == "HANDS")     return ARMORSLOT::HANDS;
    if (str == "HEAD")      return ARMORSLOT::HEAD;
    if (str == "LEGS")      return ARMORSLOT::LEGS;
    if (str == "SHOULDER")  return ARMORSLOT::SHOULDER;
    if (str == "WAIST")     return ARMORSLOT::WAIST;
    if (str == "WRIST")     return ARMORSLOT::WRIST;
    if (str == "CLOAK")     return ARMORSLOT::CLOAK;
    if (str == "SHIELD")    return ARMORSLOT::SHIELD;

    throw std::runtime_error("Unknown ARMORSLOT: " + str);
}

CONSUMABLETYPE ItemDatabase::parseConsumableType(const std::string& str) {
    if (str == "POTION")    return CONSUMABLETYPE::POTION;
    if (str == "BUFF")      return CONSUMABLETYPE::BUFF;
    if (str == "THROWABLE") return CONSUMABLETYPE::THROWABLE;
    if (str == "POISON")    return CONSUMABLETYPE::POISON;
    if (str == "ELIXIR")    return CONSUMABLETYPE::ELIXIR;

    throw std::runtime_error("Unknown ConsumableType: " + str);
}

std::vector<std::string> ItemDatabase::splitLine(const std::string& line, char delim) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, delim)) {
        fields.push_back(field);
    }

    return fields;
}

void ItemDatabase::printWeapon(const WeaponDef& def) const {
    std::cout
        << "id=" << def.weapon_id
        << "\n";
}
