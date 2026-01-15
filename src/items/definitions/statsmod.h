#pragma once

#include <utility>
#include <optional>

struct StatModifier {
    std::optional<std::pair<int, int>> damage;
    std::optional<int> armor;
    std::optional<float> speed;
    std::optional<int> health;


    StatModifier() = default;

    StatModifier operator+(const StatModifier& other) const
    {
        StatModifier result;
        result.damage = addOptPair(damage, other.damage);
        result.armor = addOpt(armor, other.armor);
        result.speed = addOpt(speed, other.speed);
        result.health = addOpt(health, other.health);
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
