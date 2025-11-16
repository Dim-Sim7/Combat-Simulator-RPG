
#include "entity.h"
#include <iostream>
#include <random>

Entity::Entity() :  stats(), HP(), abilities(), name(""){} //initialiser default list construction

Entity::Entity(const StatBlock& statsInit, 
    const point_t& hpInitCurr, 
    const point_t& hpInitMax, 
    const std::vector<Abilities>& abilitiesInit,
    const std::string& inName)
    : stats(statsInit), HP(hpInitMax, hpInitCurr), abilities(abilitiesInit), name(inName)
{}

std::string Entity::getEntityName() { return name; }
void Entity::setEntityName(const std::string& inName) 
{
    name = inName;
}

StatBlock& Entity::getStats() { return stats; }
PointWell& Entity::getHP() { return HP; }
std::vector<Abilities>& Entity::getAbilities() { return abilities; }

const StatBlock& Entity::getStats() const { return stats; }
const PointWell& Entity::getHP() const { return HP; }
const std::vector<Abilities>& Entity::getAbilities() const { return abilities; }

void Entity::setStats(StatBlock inStats) { stats = std::move(inStats); } //move into the memory address of the new stats value
void Entity::setHP(PointWell inHP) { HP = std::move(inHP); }
void Entity::setAbilities(std::vector<Abilities> inAbilities) { abilities = std::move(inAbilities); }

void Entity::addAbility(const Abilities& ability) { abilities.push_back(ability); }

double Entity::getNextAutoAttackTime() const { return nextAutoAttackTime; }
void Entity::setNextAutoAttackTime(double t) { nextAutoAttackTime = t; }

double Entity::getNextGlobalCooldownEnd() const { return nextGlobalCooldownEnd; }
void Entity::setNextGlobalCooldownEnd(double t) { nextGlobalCooldownEnd = t; }

double Entity::getAttackSpeed() const { return attackSpeed; }
double Entity::getGlobalCooldown() const { return globalCooldown; }

bool Entity::isDead()
{
    if (HP.getCurrent() == 0)
    {
        return true;
    }
    return false;
}

bool Entity::isCrit()
{
    
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(1, 100);

    int randomNumber = distrib(gen);

    return randomNumber <= 5;
        
}


