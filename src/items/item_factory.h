#pragma once
#include "item.h"
#include "definitions/weapon_def.h"
#include "definitions/armor_def.h"
#include "definitions/consumable_def.h"
#include "loot_context.h"
//This class is responsible for creating items based on itemId and table of specific items (armor, weapon, cons, etc)

class ItemFactory {
public:

    ItemFactory(const std::unordered_map<int, ItemDef>& baseItems);
    void load();

    std::unique_ptr<Item> build(int id, const LootContext& ctx) const;

private:
    const std::unordered_map<int, ItemDef>& baseItems_;
    std::unordered_map<int, WeaponDef> weapons_;
    std::unordered_map<int, ArmorDef> armors_;
    std::unordered_map<int, ConsumeDef> consumables_;

    std::unique_ptr<Item> buildWeapon(const ItemDef& base, const WeaponDef& weaponDef, const LootContext& ctx) const;
    std::unique_ptr<Item> buildArmor(const ItemDef& base, const ArmorDef& armorDef, const LootContext& ctx) const;
    std::unique_ptr<Item> buildConsumable(const ItemDef& base, const ConsumableDef& consumableDef, const LootContext& ctx) const;
};