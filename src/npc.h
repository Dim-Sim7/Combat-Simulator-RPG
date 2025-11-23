#pragma once

#include "entity.h"
#include "npc.h"
#include <cstdint>
#include <random>

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
    
    ~NPC() {}

   
    void onDeath() override
    {
        std::cout << getEntityName() << " has died!" << '\n';
        ~NPC(); 
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
    LootTable loot;
    bool hasEscaped = false;

};
