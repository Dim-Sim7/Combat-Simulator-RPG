#include "statblock.h"
#include <random>
#include <algorithm> // for std::swap

// ----- Constructors -----
StatBlock::StatBlock() 
    : damage({0, 0}), armor{1u}, level{1u} {}

StatBlock::StatBlock(std::pair<stat_t, stat_t> dmg, stat_t arm, stat_t lvl)
    : damage(dmg), armor(arm), level(lvl) {}


// ----- Getters -----
std::pair<stat_t, stat_t> StatBlock::getDamageRange() const { return damage; }
stat_t StatBlock::getArmor() const { return armor; }
stat_t StatBlock::getLevel() const { return level; }


// ----- Setters -----
void StatBlock::setDamage(const std::pair<stat_t, stat_t>& inDamage) {
    damage = inDamage;
    if (damage.first > damage.second)
        std::swap(damage.first, damage.second);
}

void StatBlock::setArmor(stat_t inArmor) {
    armor = inArmor;
}

void StatBlock::setLevel(stat_t inLevel) {
    level = inLevel;
}


// ----- Increment Methods -----
void StatBlock::increaseDamage(const std::pair<stat_t, stat_t>& dmg) {
    damage.first  += dmg.first;
    damage.second += dmg.second;
}

void StatBlock::increaseArmor(stat_t arm) {
    armor += arm;
}

void StatBlock::levelUp() {
    ++level;
    armor = static_cast<stat_t>(armor * 1.2);
    damage.first  = static_cast<stat_t>(damage.first * 1.2);
    damage.second = static_cast<stat_t>(damage.second * 1.2);
    std::cout << "Leveled Up! You are now level " << level << '\n';
}


// ----- Utility -----
stat_t StatBlock::rollDamage() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<stat_t> dist(damage.first, damage.second);
    return dist(gen);
}
