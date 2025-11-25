#pragma once
#include <cstdint>
#include <utility>
#include <random>

enum class ABILITYTYPE {
    INSTANT,
    CAST,
    CHANNEL,
    DOT,
    HEAL,
    BUFF
};
typedef ABILITYTYPE ability_t;

class Abilities {
public:

    Abilities();

    Abilities(const std::string& nameInit,
    const std::pair<int, int>& amountRangeInit,
    int cdInit,
    int castTimeInit,
    float durationInit = 0.0f, // Default value here
    ability_t typeInit = ability_t::INSTANT);

    int rollDamage() const;

    const std::pair<int, int>& getAmountRange() const;

    bool isOffCD(float currentTime) const;
    bool isOffensive();
    void use(float currentTime);
    
    const std::string& getName() const;
    ability_t getType() const;
    float getCastTime() const;
    float getDuration() const;

    float getLastUsed() const;
    float getCooldown() const;

private:
    std::string name;
    std::pair<int, int> amountRange;
    float cd;
    float castTime;
    float duration; // for DoTs, HoTs
    ability_t type; //INSTANT, CAST, ETC...
    float lastUsedTime; //tracks cds


};
