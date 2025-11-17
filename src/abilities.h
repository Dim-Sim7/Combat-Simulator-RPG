#pragma once
#include <cstdint>
#include <utility>
#include <random>

typedef std::uint32_t damage_t;
enum class ABILITYTYPE {
    INSTANT,
    CAST,
    CHANNEL,
    DOT,
};
typedef ABILITYTYPE ability_t;

class Abilities {
public:


    //DEFAULT CONSTRUCTOR
    Abilities()
        : name{""}, amountRange({0, 0}), cd(0), castTime(0), 
           lastUsedTime(0), duration(0), type(ABILITYTYPE::INSTANT), isOffensive(false) {}

    //PARAMETER CONSTRUCTOR
    Abilities(const std::string& nameInit,
    const std::pair<damage_t, damage_t>& amountRangeInit,
    u_int8_t cdInit,
    u_int8_t castTimeInit,
    float durationInit = 0.0f,
    ability_t typeInit = ability_t::INSTANT,
    bool isOffensiveInit)
        : name(nameInit), amountRange(amountRangeInit), cd(cdInit), castTime(castTimeInit), lastUsedTime(0), duration(durationInit), type(typeInit), isOffensive(isOffensiveInit)
        {}

    damage_t rollDamage() const
    {
        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<damage_t> dist(amountRange.first, amountRange.second);
        return dist(gen);
    }

    const std::pair<damage_t, damage_t>& getAmountRange() const { return amountRange; }

    bool isOffCD(float currentTime) const {
        return (currentTime - lastUsedTime) >= cd;
    }

    bool isOffensive()
    {
        return isOffensive;
    }

    void use(float currentTime) {
        lastUsedTime = currentTime;
    }
    
    const std::string& getName() const { return name; }
    ability_t getType() const { return type; }
    float getCastTime() const { return castTime; }
    float getDuration() const { return duration; }

private:
    std::string name;
    std::pair<damage_t, damage_t> amountRange;
    u_int8_t cd;
    u_int8_t castTime;
    ability_t type; //INSTANT, CAST, ETC...
    float duration; // for DoTs, HoTs
    float lastUsedTime; //tracks cds
    bool isOffensive;


};
