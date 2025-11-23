#include "statblock.h"
#include <random>
#include <algorithm> // for std::swap

// ----- Constructors -----
StatBlock::StatBlock() 
    : damage({0, 0}), armor{1u}, level{1u} {}

StatBlock::StatBlock(std::pair<int, int> dmg, int arm, int lvl)
    : damage(dmg), armor(arm), level(lvl) {}


// ----- Getters -----
std::pair<int, int> StatBlock::getDamageRange() const { return damage; }
int StatBlock::getArmor() const { return armor; }
int StatBlock::getLevel() const { return level; }


// ----- Setters -----
void StatBlock::setDamage(const std::pair<int, int>& inDamage) {
    damage = inDamage;
    if (damage.first > damage.second)
        std::swap(damage.first, damage.second);
}

void StatBlock::setArmor(int inArmor) {
    armor = inArmor;
}

void StatBlock::setLevel(int inLevel) {
    level = inLevel;
}


// ----- Increment Methods -----
void StatBlock::increaseDamage(const std::pair<int, int>& dmg) {
    damage.first  += dmg.first;
    damage.second += dmg.second;
}

void StatBlock::increaseArmor(int arm) {
    armor += arm;
}

void StatBlock::levelUp() {
    ++level;
    armor = static_cast<int>(armor * 1.2);
    damage.first  = static_cast<int>(damage.first * 1.2);
    damage.second = static_cast<int>(damage.second * 1.2);
    std::cout << "Leveled Up! You are now level " << level << '\n';
}


// ----- Utility -----
int StatBlock::rollDamage() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(damage.first, damage.second);
    return dist(gen);
}
