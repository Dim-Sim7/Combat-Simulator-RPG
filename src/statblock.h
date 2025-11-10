#pragma once
#include <cstdint>
#include <utility>
#include <random>
typedef std::uint32_t stat_t; //unsinged 32 int for stat_ts (damage can be > 16 int)

class StatBlock {
    std::pair<stat_t, stat_t> damage;
    stat_t armor;
    stat_t level;
    
    public:

    StatBlock() : damage({0, 0}), armor{1u}, level{1u} {}
    
        explicit StatBlock(std::pair<stat_t, stat_t> dmg, stat_t arm, stat_t lvl)
            : damage(dmg), armor(arm), level(lvl) //initialiser list. damage and armor are constructed directly with values
        {

        }

        std::pair<stat_t, stat_t> getDamage() const { return damage; }
        stat_t getArmor() const { return armor; }
        stat_t getLevel() const { return level; }

        void setDamage(const std::pair<stat_t, stat_t>& inDamage)
        {
            if (inDamage.first >= 0)  damage.first  = inDamage.first;
            if (inDamage.second >= 0) damage.second = inDamage.second;
            if (damage.first > damage.second) //if damage is not in ascending order, swap
                std::swap(damage.first, damage.second);
        }

        void setArmor(const stat_t& inArmor)
        {
            if (inArmor >= 0) armor = inArmor;
        }

        void setLevel(const stat_t& inLevel)
        {
            if (inLevel >= 0) level = inLevel;
        }

        void increaseDamage(const std::pair<stat_t, stat_t>& dmg) //pass by reference. New dmg object is NOT made, instead im accessing the object in memory directly
        {
            damage.first += dmg.first;
            damage.second += dmg.second;
        }

        void increaseArmor(const stat_t& arm) //const stat_t& means no copy and no modify
        {
            armor += arm;
        }

        void levelUp()
        {
            level++;
            armor *= 1.2;
            damage.first *= 1.2;
            damage.second *= 1.2;
            std::cout << "Leveled Up! You are now level " << level << '\n';
        }

        stat_t getDamage()
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<stat_t> dist(damage.first, damage.second);
            return dist(gen);
        }


};



