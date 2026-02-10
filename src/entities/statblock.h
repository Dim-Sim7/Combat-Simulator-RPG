#pragma once
#include <cstdint>
#include <utility>
#include <iostream>     // for std::cout in levelUp()
#include "../items/definitions/statsmod.h"

/**
 * @brief Holds base combat statistics for an entity (damage, armor, level).
 * 
 * Provides basic manipulation methods for increasing, retrieving, and 
 * leveling up stats. Damage values are represented as a range (min, max).
 */
class StatBlock {
private:
    //BASE STATS
    std::pair<int, int> damage;  // Damage range (min, max)
    int armor;                      // Defensive stat
    int level;                      // Current level of the entity
    float critChance;
    //BONUS STATS FROM ARMOR, BUFFS, ETC...
    std::pair<int, int> bonusDamage;
    std::optional<int> bonusArmor;
    std::optional<int> bonusCrit;
    std::optional<int> bonusHealth;
public:

    StatBlock();

    StatBlock(std::pair<int, int> dmg, int arm, int lvl);

    [[nodiscard]] std::pair<int, int> getDamageRange() const;
    [[nodiscard]] int getArmor() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] float getCritChance() const;

    void setBaseDamage(const std::pair<int, int>& inDamage);
    void setBaseArmor(int inArmor);
    void setLevel(int inLevel);

    void increaseDamage(const std::pair<int, int>& dmg);
    void increaseArmor(int arm);
    void increaseCritChance(float inCrit);
    void levelUp();

    [[nodiscard]] int rollDamage() const;

    void applyStatModifier(const StatModifier& mod);

};
