
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

void Entity::attack(Entity& target, float currentTime) //attack with base damage, will always have a target
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

void Entity::castSpell(Entity* target, Abilities& spell, float currentTime) //attack with spell, might not always be targeted (aoe, buff)
{
    if (!spell.isOffCD(currentTime)) 
    {
        std::cout << spell.getName() << " is on cooldown!\n";
        return;
    }

    if (currentTime < nextGlobalCooldownEnd)
    {
        std::cout << "Not ready yet\n";
        return;
    }
    
    //Instant spell
    if (spell.getType() == ABILITYTYPE::INSTANT)
    {
        spell.use(currentTime);
        damage_t damage = spell.getDamage();
        if (isCrit())
            damage *=2;
        target->takeDamage(damage);
        
        std::cout << name << " cast " << spell.getName()
        << " on " << target->getEntityName()
        << " for " << damage << " damage!\n";
        nextGlobalCooldownEnd = currentTime + globalCooldown;
    }

    cast.isCasting = true;
    cast.castStart = currentTime;
    cast.castEnd = currentTime + spell.getCastTime();
    cast.spell = &spell;
    cast.target = target;
    std::cout << name << " begins casting " 
                << spell.getName() 
                << " (" << spell.getCastTime() << "s)" << "\n";

}


void Entity::takeDamage(const damage_t& damage)
{
    float reduction = calcDamageReduction();
    damage_t finalDamage = static_cast<damage_t>(damage * (1.0f - reduction));
    HP.reduceCurrent(finalDamage);
    if (isDead())
        onDeath();
}

void Entity::heal(const damage_t& heal) 
{
    HP.increaseCurrent(heal);
}

float Entity::calcDamageReduction() const 
{
    float armor = static_cast<float>(stats.getArmor());
    float reduction = armor / (armor + 400.0f + (85.0f * stats.getLevel()));
    return reduction;
}




