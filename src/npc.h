#pragma once

#include "entity.h"
#include "npc.h"
#include <cstdint>
#include <random>

//enemy. Has a loot table (inventory), health, damage, spells. Basically same as player without leveling system
//on death, an enemy can drop items. Enemies are created from scraped data on classicdb.

class NPC: public Entity {
public:
    NPC() : Entity() {}
    
    NPC(const StatBlock& statsInit, 
            const point_t& hpInitCurr, 
            const point_t& hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& nameInit)
            : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit) {}
    
    ~NPC() {}

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


    void takeDamage(const damage_t& damage) override 
    {
        float reduction = calcDamageReduction();
        damage_t finalDamage = static_cast<damage_t>(damage * (1.0f - reduction));
        HP.reduceCurrent(finalDamage);
        if (isDead())
            onDeath();
    }

    void heal(const damage_t& heal) override 
    {
        HP.increaseCurrent(heal);
    }

    float calcDamageReduction() const 
    {
        float armor = static_cast<float>(stats.getArmor());
        float reduction = armor / (armor + 400.0f + (85.0f * stats.getLevel()));
        return reduction;
    }

    void onDeath() override
    {
        std::cout << getEntityName() << " has died!" << '\n';
        ~NPC(); 
    }
    
    void escapeCombat()
    {
        hasEscaped = true;
        std::cout << name << " is trying to flee... and escapes the battle!\n";
    }

    bool hasFledCombat() const
    {
        return hasEscaped;
    }


private:
    LootTable loot;
    bool hasEscaped = false;'
    '



};
