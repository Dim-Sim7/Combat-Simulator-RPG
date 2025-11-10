#pragma once
#include <cstdint>
#include <utility>

typedef std::uint32_t damage_t;
enum class AbilityType {
    INSTANT,
    CAST,
    CHANNEL,
    DOT,
    HEAL
};
typedef AbilityType ability_t;

class Abilities {
public:


    //DEFAULT CONSTRUCTOR
    Abilities()
        : name{""}, amountRange({0, 0}), cd{0}, castTime{0}, 
          type(AbilityType::INSTANT), lastUsedTime{0}, duration{0} {}

    //PARAMETER CONSTRUCTOR
    Abilities(const std::string& nameInit,
    std::pair<damage_t, damage_t>& amountRangeInit,
    u_int8_t& cdInit,
    u_int8_t& castTimeInit,
    ability_t typeInit,
    float durationInit = 0.0f)
        : name(nameInit), amountRange(amountRangeInit), cd(cdInit), castTime(castTimeInit), type(typeInit), duration(durationInit), lastUsedTime(0)
        {}

    damage_t getDamage() const
    {
        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<damage_t> dist(amountRange.first, amountRange.second);
        return dist(gen);
    }

    bool isOffCD(float currentTime) const {
        return (currentTime - lastUsedTime) >= cd;
    }

    void use(float currentTime) {
        lastUsedTIme = currentTime;
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



};
