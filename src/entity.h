#pragma once
#include "pointwell.h"
#include "statblock.h"
#include "abilities.h"
#include <iostream>
#include <memory>
#include <vector>
#include <random>

//Typedef for damage type
typedef uint32_t damage_t;
/**
 * @brief Entity represents either a player or NPC.
 * Provides virtual methods to be implemented by children
 * has implemented methods that are the same regardless of children
 */
class Entity {
public:
    Entity();
    explicit Entity(const StatBlock& statsInit, 
        const point_t& hpInitCurr, 
        const point_t& hpInitMax, 
        const std::vector<Abilities>& abilitiesInit,
        const std::string& inName);

    //-------- GETTERS ---------
    StatBlock& getStats();
    PointWell& getHP();
    std::vector<Abilities>& getAbilities();

    const StatBlock& getStats() const; //const after states that this method cannot modify member variables in general
    const PointWell& getHP() const; //const before states that I will not modify the thing being called. Const after is added to differentiate to the compiler the other non-const getters
    const std::vector<Abilities>& getAbilities() const;

    std::string getEntityName() override { return name; }

    //-------- SETTERS ---------
    void setStats(StatBlock inStats);
    void setHP(PointWell inHP);
    void setAbilities(std::vector<Abilities> inAbilities);
    //-------- UTILITY ---------
    bool isDead();
    bool isCrit();

    void addAbility(const Abilities& ability);

    std::string getEntityName() 
    void setEntityName(const std::string& inName);
    
    virtual void attack(Entity& target, float currentTime) = 0;
    virtual void castSpell(Entity* target, Abilities& spell, float currentTime) = 0;

    virtual void takeDamage(const damage_t& damage) = 0;
    virtual void heal(const damage_t& heal) = 0;
    virtual void onDeath() = 0;

    double getNextAutoAttackTime() const;
    void setNextAutoAttackTime(double t);

    double getNextGlobalCooldownEnd() const;
    void setNextGlobalCooldownEnd(double t);

    double getAttackSpeed() const;
    double getGlobalCooldown() const;

protected:
    StatBlock stats;
    PointWell HP; //unique ptr manages each object individually and makes sure it gets deleted in mem when out of scope
    std::vector<Abilities> abilities;
    std::string name;
    
    
    
    double nextAutoAttackTime = 0.0;
    double nextGlobalCooldownEnd = 0.0;
    double attackSpeed = 2.6; // e.g. 2.6s weapon speed
    double globalCooldown = 1.5; // standard GCD
};
