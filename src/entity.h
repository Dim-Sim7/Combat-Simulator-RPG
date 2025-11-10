#pragma once
#include "pointwell.h"
#include "statblock.h"
#include "abilities.h"
#include <iostream>
#include <memory>
#include <vector>

typedef uint32_t damage_t;

class Entity {
    public:

        bool isDead()
        {
            if (HP.getCurrent() == 0)
            {
                return true;
            }
            return false;
        }

    virtual std::string getEntityName() = 0;
    
    virtual void attack(Entity& target, float currentTime) = 0;
    virtual void castSpell(Entity* target, Abilities& spell, float currentTime) = 0;

    virtual void takeDamage(const damage_t& damage) = 0;
    virtual void heal(const damage_t& heal) = 0;

    double nextAutoAttackTime = 0.0;
    double nextGlobalCooldownEnd = 0.0;
    double attackSpeed = 2.6; // e.g. 2.6s weapon speed
    double globalCooldown = 1.5; // standard GCD

    protected:
        StatBlock stats;
        PointWell HP; //unique ptr manages each object individually and makes sure it gets deleted in mem when out of scope
        std::vector<Abilities> abilities;
        std::string name;
        Entity() :  stats(), HP(), abilities(), name(""){} //initialiser default list construction
        
        explicit Entity(const StatBlock& statsInit, 
            const point_t& hpInitCurr, 
            const point_t& hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& inName)
            : stats(statsInit), HP(hpInitMax, hpInitCurr), abilities(abilitiesInit), name(inName)
        {}
    
        bool isCrit()
        {
            bool isCrit = false;
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<> distrib(1, 100);

            int randomNumber = distrib(gen);

            if (randomNumber <= 5)
                isCrit = true;
            

            return isCrit;
        }

        virtual void onDeath() = 0;

};
