#pragma once
#include <cstdint>
#include <utility>
#include <iostream>     // for std::cout in levelUp()

// Type alias for character stats (32-bit unsigned integer)


/**
 * @brief Holds base combat statistics for an entity (damage, armor, level).
 * 
 * Provides basic manipulation methods for increasing, retrieving, and 
 * leveling up stats. Damage values are represented as a range (min, max).
 */
class StatBlock {
private:
    std::pair<int, int> damage;  // Damage range (min, max)
    int armor;                      // Defensive stat
    int level;                      // Current level of the entity

public:
    /// Default constructor initializes all values to base starting stats
    StatBlock();

    /// Parameterized constructor
    StatBlock(std::pair<int, int> dmg, int arm, int lvl);

    // ----- Getters -----
    [[nodiscard]] std::pair<int, int> getDamageRange() const;
    [[nodiscard]] int getArmor() const;
    [[nodiscard]] int getLevel() const;

    // ----- Setters -----
    void setDamage(const std::pair<int, int>& inDamage);
    void setArmor(int inArmor);
    void setLevel(int inLevel);

    // ----- Increment Methods -----
    void increaseDamage(const std::pair<int, int>& dmg);
    void increaseArmor(int arm);
    void levelUp();

    // ----- Utility -----
    /// Returns a random damage roll between min and max
    [[nodiscard]] int rollDamage() const;
};
