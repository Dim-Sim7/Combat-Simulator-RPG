#include "item_factory.h"



ItemFactory::ItemFactory(std::unordered_map<ItemdId, ItemDef>& baseItems) 
:   baseItems_(baseItems) {}

void ItemFactory::load() {
    //TO DO
    // load all item definitions
    // read all .csvs
    // store in each map

}

std::unique_ptr<Item> ItemFactory::build(int id, const LootContext& ctx) const {
    const ItemDef& base = baseItems_.at(id);

    switch (base.type) {
        case ItemType::Weapon:
            return buildWeapon(base, weapons_.at(id), LootContext& ctx);

        case ItemType::Armor:
            return buildArmor(base, armors_.at(id), LootContext& ctx);

        case ItemType::Consumable:
            return buildConsumable(base, consumable_.at(id), LootContext& ctx);

    }

    throw std::logic_error("Unknown item type");

}

// struct LootContext {
//     int level; //level of loot source
//     MobType mobType; //humanoids drop more gold

//     EncounterType encounterType;   // Normal / Elite / Boss
//     LocationType locationType;     // Overworld / Dungeon

//     //OPTIONAL
//     std::optional<int> chestTier;
// // };
// struct StatModifier {
//     std::optional<std::pair<int, int>> damage;
//     std::optional<int> armor;
//     std::optional<float> speed;
//     std::optional<int> health;

    // void setDamageBuff(std::pair<int, int> inDamage);

    // void setSpeedBuff(float inSpeed);
    // void setArmorBuff(int inArmor);

    // void setHealthBuff(int inHealth);


//REMINDER - ALL ITEMS HAVE A STATMOD IN-BUILT. TO INCREASE STATS, USE THIS
//roll rarity here. Higher level mobs have higher chance of rarity
//bosses always drop high rarity
//elites have high chance of rarity
std::unique_ptr<Item> ItemFactory::buildWeapon(const ItemDef& base, const WeaponDef& weaponDef, const LootContext& ctx) const {
    //for weapons, increase damage based on level. adjust name with prefixes and suffixes
    //roll rari
    return Weapon{base.name, weaponDef.weapon_id, weaponDef.minDamage, weaponDef.maxDamage, weaponDef.speed, weaponDef.type};
}

std::unique_ptr<Item> ItemFactory::buildArmor(const ItemDef& base, const ArmorDef& armorDef, const LootContext& ctx) const {
    return Armor{base.name, armorDef.armor_id, armorDef.maxDurability, armorDef.armorType, armorDef.armorSlot};
}

std::unique_ptr<Item> ItemFactory::buildConsumable(const ItemDef& base, const ConsumableDef& consumableDef, const LootContext& ctx) const {
    return Consumable{base.name, consumableDef.consumable_id, consumableDef.stack_size, consumableDef.stackable,
                    consumableDef.duration, consumableDef.statMod, consumableDef.consumable_type};
}

void ItemFactory::loadBaseItems() {
        std::ifstream file("base_item_table.h");
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return 1;
        }
        std::string line;
        // Skip header
        std::getline(file, line);

        while (std::getline(file, line)) {
            // to do...
        }

}