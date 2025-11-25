#pragma once

#include "entity.h"
#include <cstdint>
#include <random>
#include <iostream>

//enemy. Has a loot table (inventory), health, damage, spells. Basically same as player without leveling system
//on death, an enemy can drop items. Enemies are created from scraped data on classicdb.

class NPC: public Entity {
public:
    NPC() : Entity() {}
    
    NPC(const StatBlock& statsInit, 
            const int& hpInitCurr, 
            const int& hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& nameInit)
            : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit) {}
    

   
    bool hasPotion() const
    {
        // for (const auto& item : loot.getItems())
        // {
        //     if (item->getType() == ITEMTYPE::CONSUMABLE)
        //     {
        //         return true;
        //     }
        // }
        // return false;
        return false;
    }

    void usePotion()
    {
        // for (auto& item : loot.getItems())
        // {
        //     if (item->getType() == ITEMTYPE::CONSUMABLE)
        //     {
        //         std::cout << name << " uses a " << item->getName() << "!\n";
        //         //apply potion effects here
        //         loot.removeItem(item);
        //         return;
        //     }
        // }
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

    int expOnDeath()
    {
        return ((5 * stats.getLevel()) + 45) * 15; //added x15 exp gain multiplier (to speed things up)
    }


private:
    //LootTable loot;
    bool hasEscaped = false;

};
