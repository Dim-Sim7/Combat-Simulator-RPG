#pragma once

#include "entity.h"
#include "npc.h"
#include "abilities_pool.h"
#include <cstdint>
#include <random>

typedef std::uint64_t exp_t;

//player class. Handles playable character. Attacking, cast spells, leveling, death
class Player: public Entity {

    public:
        Player() : Entity(), currEXP(0u), expToLevel(100u) {}

        Player(const StatBlock& statsInit, 
            const point_t& hpInitCurr, 
            const point_t& hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& nameInit)
            : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit), //calls Entity's parameterized constructor
            currEXP(0u), 
            expToLevel(100u) {}

        
        void gainExp(exp_t earnedEXP)
        {
            currEXP += earnedEXP;
            if (currEXP >= expToLevel)
            {
                currEXP = 0;
                expToLevel *= 2;
                levelUp();
            }
        }

        void attack(Entity& target, float currentTime) override //attack with base damage, will always have a target
        {
            // Prevent attacking before the next swing
            if (currentTime < nextAutoAttackTime)
                return;
            damage_t damage = stats.rollDamage();
            if (isCrit())
                damage *= 2;
            target.takeDamage(damage);

            std::cout << name << " hits " << target.getEntityName()
              << " for " << damage << " damage!\n";

            // Schedule next swing
            nextAutoAttackTime = currentTime + attackSpeed;

            // Trigger global cooldown
            nextGlobalCooldownEnd = currentTime + globalCooldown;
        }

        void castSpell(Entity* target, Abilities& spell, float currentTime) override //attack with spell, might not always be targeted (aoe, buff)
        {
            if (!spell.isOffCD(currentTime)) {
                std::cout << spell.getName() << " is on cooldown!\n";
                return;
            }

            //Trigger cooldown
            spell.use(currentTime);
            damage_t damage = spell.getDamage();
            if (isCrit())
                damage *=2;
            target->takeDamage(damage);

            std::cout << name << " cast " << spell.getName()
            << " on " << target->getEntityName()
            << " for " << damage << " damage!\n";

            //update GCD end
            nextGlobalCooldownEnd = currentTime + globalCooldown;

        }


        void takeDamage(const damage_t& damage) override {
            float reduction = calcDamageReduction();
            damage_t finalDamage = static_cast<damage_t>(damage * (1.0f - reduction));
            HP.reduceCurrent(finalDamage);
            if (isDead())
                onDeath();
        }

        void heal(const damage_t& heal) override {
            HP.increaseCurrent(heal);
        }

        float calcDamageReduction() const {
            float armor = static_cast<float>(stats.getArmor());
            float reduction = armor / (armor + 400.0f + (85.0f * stats.getLevel()));
            return reduction;
        }


    private:
        exp_t currEXP;
        exp_t expToLevel;
        AbilitiesPool aPool;
        Inventory inventory;

        void onDeath() override
        {
            std::cout << getEntityName() << " has died!" << '\n';
        }

        void levelUp()
        {
            stats.levelUp();
            
            Abilities newAbility = aPool.getRandomAbility(abilities);

            if (newAbility.getName() != "None") {
                abilities.push_back(newAbility);
                std::cout << name << " learned a new ability: " << newAbility.getName() << "!\n";
            }
            
        }

    




};
