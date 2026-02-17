#pragma once

#include "entity.h"
#include <vector>
#include <string>

enum class ConsumableType {
    Heal,
    Buff,
    Damage
};

struct Consumable {
    ConsumableType type;
    int value;
};

class NPC : public Entity {
public:
    NPC() = default;

    NPC(const StatBlock& statsInit,
        int hpInitCurr,
        int hpInitMax,
        const std::vector<Abilities>& abilitiesInit,
        const std::string& nameInit);

    bool hasPotion() const;
    void usePotion();
    void generateConsumables();
    void escapeCombat();
    bool hasFledCombat() const;
    int expOnDeath() const;

private:
    bool hasEscaped = false;
    std::vector<Consumable> consumables;
};
