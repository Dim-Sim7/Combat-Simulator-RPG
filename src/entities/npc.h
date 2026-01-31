#pragma once

#include "entity.h"
#include <cstdint>
#include <random>
#include <iostream>

//enemy. Has a loot table (inventory), health, damage, spells. Basically same as player without leveling system
//on death, an enemy can drop items. Enemies are created from scraped data on classicdb.

enum class ConsumableType {
    Heal, Buff, Damage
}
struct Consumable {
    ConsumableType type;
    int value;
};
class NPC: public Entity {
public:
    NPC() = default;
    
    NPC(const StatBlock& statsInit, 
            int hpInitCurr, 
            int hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& nameInit);
    
    bool hasPotion() const
    {
        //if any 
        return std::any_of(consumables.begin(), consumables.end(),
                [](const Consumable& c) {
                    return c.type == ConsumableType::Heal;
                });
    }

    void usePotion()
    {
        auto it = std::find_if(consumables.begin(), consumables.end(),
            [](const Consumable& c) {
                return c.type == ConsumableType::Heal;
            });
        if (it == consumables.end()) return;

        heal(it->value);
        consumables.erase(it);
    }

    generateConsumables() {
        int lvl = stats.getLevel();

        if (lvl >= 5 && (randomFloat(0.0f, 1.0f) <= 0.35f))
            consumables.push_back({ConsumableType::Heal, 25});

    }

    void escapeCombat()
    {
        hasEscaped = true;
        std::cout << name << " is trying to flee... and escapes the battle!\n";
    }

    bool hasFledCombat() const
    {
        return hasEscaped;
    }

    int expOnDeath() const
    {
        return ((5 * stats.getLevel()) + 45) * 15; //added x15 exp gain multiplier (to speed things up)
    }


private:
    //LootTable loot;
    bool hasEscaped = false;
    std::vector<Consumable> consumables;
};
