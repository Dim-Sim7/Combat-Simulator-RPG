#pragma once
#include <cstdint>
#include <utility>
#include <iostream>     // for std::cout in levelUp()

// Type alias for character stats (32-bit unsigned integer)
using stat_t = std::uint32_t;

/**
 * @brief Holds base combat statistics for an entity (damage, armor, level).
 * 
 * Provides basic manipulation methods for increasing, retrieving, and 
 * leveling up stats. Damage values are represented as a range (min, max).
 */
class StatBlock {
private:
    std::pair<stat_t, stat_t> damage;  // Damage range (min, max)
    stat_t armor;                      // Defensive stat
    stat_t level;                      // Current level of the entity

public:
    /// Default constructor initializes all values to base starting stats
    StatBlock();

    /// Parameterized constructor
    StatBlock(std::pair<stat_t, stat_t> dmg, stat_t arm, stat_t lvl);

    // ----- Getters -----
    [[nodiscard]] std::pair<stat_t, stat_t> getDamageRange() const;
    [[nodiscard]] stat_t getArmor() const;
    [[nodiscard]] stat_t getLevel() const;

    // ----- Setters -----
    void setDamage(const std::pair<stat_t, stat_t>& inDamage);
    void setArmor(stat_t inArmor);
    void setLevel(stat_t inLevel);

    // ----- Increment Methods -----
    void increaseDamage(const std::pair<stat_t, stat_t>& dmg);
    void increaseArmor(stat_t arm);
    void levelUp();

    // ----- Utility -----
    /// Returns a random damage roll between min and max
    [[nodiscard]] stat_t rollDamage() const;
};
