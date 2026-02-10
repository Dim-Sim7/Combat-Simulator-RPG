#pragma once

#include "../loot/loot_context.h"
#include "item_database.h"
#include "item.h"
#include "weapon.h"
#include "armor.h"
#include "consumable.h"
//This class is responsible for creating items based on itemId and table of specific items (armor, weapon, cons, etc)

struct RarityWeights {
    int common;
    int uncommon;
    int rare;
    int epic;
    int legendary;
};

constexpr RarityWeights BASE_WEIGHTS {
    60,
    25,
    10,
    4,
    1
};

class ItemFactory {
public:

    ItemFactory();
    std::unique_ptr<Item> build(int id, const LootContext& ctx) const;

private:

    ItemDatabase db;
    std::unique_ptr<Item> buildWeapon(const ItemDef& base, const WeaponDef& weaponDef, const LootContext& ctx) const;
    std::unique_ptr<Item> buildArmor(const ItemDef& base, const ArmorDef& armorDef, const LootContext& ctx) const;
    std::unique_ptr<Item> buildConsumable(const ItemDef& base, const ConsumableDef& consumableDef, const LootContext& ctx) const;

    RarityWeights applyTierModifier(RarityWeights w, EnemyTier tier);
    RarityWeights applyLevelScaling(RarityWeights w, int level);
    void clampWeights(RarityWeights& w);
    Rarity rollFromWeights(const RarityWeights& w, RNG& rng);
    Rarity rollRarity(const LootContext& ctx);
    void upgradeArmor(Armor& armor, const LootContext& ctx);
    void upgradeWeapon(Weapon& weapon, const LootContext& ctx);
};