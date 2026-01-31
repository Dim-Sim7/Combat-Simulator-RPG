#pragma once

#include <utility>
#include <optional>

/**
 * StatsMod is used for spells, consumables, weapons and armor. 
 * If an item is equipped or used, it carries a statModifier variable that
 * holds optional increases or decreases to certain stats.
 * The same goes for spell buffs and debuffs.
 * Can also be used to inflate difficulty of enemies and increases player stats on level up
 */

struct StatModifier {
    std::optional<std::pair<int, int>> damage;
    std::optional<int> armor;
    std::optional<float> speed;
    std::optional<int> health;
    std::optional<float> crit;


    StatModifier() = default;

    StatModifier operator+(const StatModifier& other) const
    {
        StatModifier result;
        result.damage = addOptPair(damage, other.damage);
        result.armor = addOpt(armor, other.armor);
        result.speed = addOpt(speed, other.speed);
        result.health = addOpt(health, other.health);
        result.crit = addOpt(crit, other.crit);
        return result;
    }

    //helper function to add optionals
    template<typename T>
    static std::optional<T> addOpt(const std::optional<T>& a, const std::optional<T>& b)
    {
        if (a && b) return *a + *b;
        if (a) return a;
        if (b) return b;
        return std::nullopt;
    }

    //helper function to add optional pairs
    static std::optional<std::pair<int,int>> addOptPair(
        const std::optional<std::pair<int,int>>& a,
        const std::optional<std::pair<int,int>>& b)
    {
        if (a && b)
            return std::make_pair(a->first + b->first, a->second + b->second);

        if (a) return a;
        if (b) return b;

        return std::nullopt;
    }
};
