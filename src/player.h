#pragma once

#include "entity.h"
#include "npc.h"
#include "abilities_pool.h"
#include "pointwell.h"
#include <cstdint>
#include <random>
#include <cmath>

//player class. Handles playable character. Attacking, cast spells, leveling, death
class Player: public Entity {

public:
    Player() : Entity(), EXP(100u, 0u) {}

    Player(const StatBlock& statsInit, 
        const point_t& hpInitCurr, 
        const point_t& hpInitMax, 
        const std::vector<Abilities>& abilitiesInit,
        const std::string& nameInit)
        : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit), //calls Entity's parameterized constructor
        EXP(100u, 0u) {}

    ~Player() {}
    
    void gainExp(point_t earnedEXP)
    {
        EXP.increaseCurrent(earnedEXP);

        std::cout << "You gain " << earnedEXP << " experience.\n";
        if (EXP.getCurrent() == EXP.getMax())
        {
            EXP.setCurrent(0);
            EXP.setMax(getEXPToLevel());
            levelUp();
        }
    }


    void onDeath() override
    {
        std::cout << getEntityName() << " has died!" << '\n';
        ~Player();
    }


private:
    PointWell EXP;
    AbilitiesPool aPool;
    Inventory inventory;

    void levelUp()
    {
        stats.levelUp();
        
        if (stats.getLevel() % 5 == 0) //Every 5 levels, gain an ability
        {
            Abilities newAbility = aPool.getRandomAbility(abilities);
            if (newAbility.getName() != "None") 
            {
                abilities.push_back(newAbility);
                std::cout << name << " learned a new ability: " << newAbility.getName() << "!\n";
            }
        }

        
    }

    point_t getEXPToLevel()
    {
        stat_t curLvl = stats.getLevel();
        point_t EXPtoLevel = 0;
        if (curLvl < 11) // level 1 to 11
        {
            EXPtoLevel = (40 * (curLvl * curLvl)) +  (360 * curLvl);
        }
        else if (curLvl < 27) // level 11 to 27
        {
            EXPtoLevel = static_cast<point_t>((-0.4 * pow(curLvl, 3)) + (40.4 * pow(curLvl, 2)) + (396 * curLvl));
        }
        else if (curLvl <= 59) //level 27 to 59
        {
            EXPtoLevel = static_cast<point_t>(((65 * pow(curLvl, 2)) - (165 * curLvl) - 6750) * 0.82);
        }
        else //level 60+
        {
            EXPtoLevel = 155 + (235 + (5 * curLvl)) * (1344 - 69 - ((69 - curLvl) * (3 + (69 - curLvl) * 4)));
        }

        return EXPtoLevel;
        
        
    }

    

};
