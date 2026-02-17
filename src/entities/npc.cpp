#include "npc.h"

#include <algorithm>
#include <iostream>
#include <random>
#include "../loot/rng.h"

// Constructor
NPC::NPC(const StatBlock& statsInit,
         int hpInitCurr,
         int hpInitMax,
         const std::vector<Abilities>& abilitiesInit,
         const std::string& nameInit)
    : Entity(statsInit, hpInitCurr, hpInitMax, abilitiesInit, nameInit)
{
}

// Check if NPC has a healing potion
bool NPC::hasPotion() const
{
    return std::any_of(consumables.begin(), consumables.end(),
        [](const Consumable& c) {
            return c.type == ConsumableType::Heal;
        });
}

// Use first healing potion found
void NPC::usePotion()
{
    auto it = std::find_if(consumables.begin(), consumables.end(),
        [](const Consumable& c) {
            return c.type == ConsumableType::Heal;
        });

    if (it == consumables.end())
        return;

    heal(it->value);
    consumables.erase(it);
}

// Generate consumables based on level
void NPC::generateConsumables()
{
    int lvl = stats.getLevel();

    if (lvl >= 5 && (randomFloat(0.0f, 1.0f) <= 0.35f))
    {
        consumables.push_back({ ConsumableType::Heal, 25 });
    }
}

// NPC flees combat
void NPC::escapeCombat()
{
    hasEscaped = true;
    std::cout << name << " is trying to flee... and escapes the battle!\n";
}

bool NPC::hasFledCombat() const
{
    return hasEscaped;
}

// XP reward on death
int NPC::expOnDeath() const
{
    return ((5 * stats.getLevel()) + 45) * 15;
}
