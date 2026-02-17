#include "statblock.h"
#include <random>
#include <algorithm> // for std::swap
#include <utility> // for std::pair
#include <iostream> // for std::cout

// ----- Constructors -----
StatBlock::StatBlock()
    : damage({1,4})
    , armor(1)
    , level(1)
    , critChance(0.05f)
    , bonusDamage({0,0})
    , bonusArmor(0)
    , bonusCrit(0)
    , bonusHealth(0)
    
{}

StatBlock::StatBlock(std::pair<int, int> dmg, int arm, int lvl)
    : damage(dmg), armor(arm), level(lvl), critChance(5), bonusDamage({0,0}), bonusArmor(0), bonusCrit(0), bonusHealth(0) {}


// ----- Getters -----
[[nodiscard]] std::pair<int,int> StatBlock::getDamageRange() const
{
    return {
        damage.first  + bonusDamage.first,
        damage.second + bonusDamage.second
    };
}

[[nodiscard]] int StatBlock::getArmor() const
{
    return armor + bonusArmor.value_or(0);
}

[[nodiscard]] int StatBlock::getLevel() const { return level; }

[[nodiscard]] float StatBlock::getCritChance() const { return critChance + bonusCrit.value_or(0.0f); }


// ----- Setters -----
void StatBlock::setBaseDamage(const std::pair<int, int>& inDamage) {
    damage.first  = std::max(0, inDamage.first);
    damage.second = std::max(inDamage.first, inDamage.second);
}

void StatBlock::setBaseArmor(int inArmor) {
    armor = std::max(0, inArmor);
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

void StatBlock::increaseCritChance(float inCrit) {
    critChance += inCrit;
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
    std::pair<int,int> finalDamage = this->getDamageRange();
    int minDmg = finalDamage.first;
    int maxDmg = finalDamage.second;
    if (minDmg > maxDmg)
        std::swap(minDmg, maxDmg);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minDmg, maxDmg);
    return dist(gen);
}

void StatBlock::applyStatModifier(const StatModifier& mod)
{
    bonusArmor  = mod.armor;
    bonusDamage = mod.damage.value_or(std::make_pair(0,0));
    bonusCrit = mod.crit;
    bonusHealth = mod.health;    
}

