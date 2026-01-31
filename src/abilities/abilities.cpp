#include "abilities.h"
#include <random>

//DEFAULT CONSTRUCTOR
Abilities::Abilities()
    : name{""}, amountRange({0, 0}), cd(0.0f), castTime(0.0f), 
         duration(0.0f), type(ABILITYTYPE::INSTANT), lastUsedTime(0.0f) {}

//PARAMETER CONSTRUCTOR
Abilities::Abilities(const std::string& nameInit,
                    const std::pair<int, int>& amountRangeInit,
                    int cdInit,
                    int castTimeInit,
                    float durationInit,
                    ability_t typeInit)
    : name(nameInit), 
    amountRange(amountRangeInit), 
    cd(cdInit), 
    castTime(castTimeInit),
    duration(durationInit), 
    type(typeInit), 
    lastUsedTime(0.0f)
    {}

int Abilities::rollDamage() const
{
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(amountRange.first, amountRange.second);
    return dist(gen);
}

const std::pair<int, int>& Abilities::getAmountRange() const { return amountRange; }

bool Abilities::isOffCD(float currentTime) const {
    return (currentTime - lastUsedTime) >= cd;
}

bool Abilities::isOffensive()
{
    return type != ABILITYTYPE::HEAL;
}

void Abilities::use(float currentTime) {
    lastUsedTime = currentTime;
}

const std::string& Abilities::getName() const { return name; }
ability_t Abilities::getType() const { return type; }
float Abilities::getCastTime() const { return castTime; }
float Abilities::getDuration() const { return duration; }


float Abilities::getLastUsed() const { return lastUsedTime; }
float Abilities::getCooldown() const { return cd; }
