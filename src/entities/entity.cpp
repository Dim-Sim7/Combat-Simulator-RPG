
#include "entity.h"
#include <iostream>
#include <random>


Entity::Entity() :  stats(), HP(), abilities(), name(""),     
    inventory(std::make_unique<Inventory>()), 
    equipSlots(std::make_unique<EquipSlots>()), 
    aPool(std::make_unique<AbilitiesPool>()) {} //initialiser default list construction

Entity::Entity(const StatBlock& statsInit, 
    const int hpInitCurr, 
    const int hpInitMax, 
    const std::vector<Abilities>& abilitiesInit,
    const std::string& inName)
    : stats(statsInit), HP(hpInitMax, hpInitCurr), abilities(abilitiesInit), name(inName),     
    inventory(std::make_unique<Inventory>()), 
    equipSlots(std::make_unique<EquipSlots>()), 
    aPool(std::make_unique<AbilitiesPool>())
{}

std::string Entity::getEntityName() const { return name; }
void Entity::setEntityName(const std::string& inName) 
{
    name = inName;
}

StatBlock& Entity::getStats() { return stats; }
PointWell& Entity::getHP() { return HP; }
std::vector<Abilities>& Entity::getAbilities() { return abilities; }
Inventory* Entity::getInventory()
{
    return inventory.get();
}

const Inventory* Entity::getInventory() const
{
    return inventory.get();
}

const StatBlock& Entity::getStats() const { return stats; }
const PointWell& Entity::getHP() const { return HP; }
const std::vector<Abilities>& Entity::getAbilities() const { return abilities; }

void Entity::setStats(StatBlock inStats) { stats = inStats; } //move into the memory address of the new stats value
void Entity::setHP(PointWell inHP) { HP = inHP; }
void Entity::setAbilities(std::vector<Abilities> inAbilities) { abilities = inAbilities; }

void Entity::addAbility(const Abilities& ability) { abilities.push_back(ability); }

double Entity::getNextAutoAttackTime() const { return nextAutoAttackTime; }
void Entity::setNextAutoAttackTime(double t) { nextAutoAttackTime = t; }

double Entity::getNextGlobalCooldownEnd() const { return nextGlobalCooldownEnd; }
void Entity::setNextGlobalCooldownEnd(double t) { nextGlobalCooldownEnd = t; }

double Entity::getAttackSpeed() const { return attackSpeed; }
double Entity::getGlobalCooldown() const { return globalCooldown; }

int Entity::getMaxHP() const { return HP.getMax(); }
int Entity::getCurrentHP() const { return HP.getCurrent(); }

bool Entity::isDead() const
{
    return HP.getCurrent() <= 0;
}

bool Entity::isCrit() const
{

    static thread_local std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution crit(stats.getCritChance());
    return crit(gen);
}
bool Entity::isCasting() const
{
    return cast.isCasting;
}

void Entity::attack(Entity& target, float currentTime) //attack with base damage, will always have a target
{
    // Prevent attacking before the next swing
    if (currentTime < nextAutoAttackTime)
        return;
    int damage = stats.rollDamage();
    /*
    zzz (apply crit chance)
    
    */
    if (isCrit()) {
        damage *= 2;
        std::cout << "Crit!\n";   
    }
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
        std::cout << spell.getName() << " is on cooldown! "<< spell.getCooldown() - (currentTime - spell.getLastUsed()) << "s remaining.\n";
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
        int damage = spell.rollDamage();
        if (isCrit())
            damage *=2;
        if (target == nullptr)
        {
            std::cout << "You cast " << spell.getName() << "!\n";
            return;
        }
        target->takeDamage(damage);
        
        std::cout << name << " cast " << spell.getName()
        << " on " << target->getEntityName()
        << " for " << damage << " damage!\n";
        nextGlobalCooldownEnd = currentTime + globalCooldown;
        return;
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

void Entity::tryCastSpell(const std::string& spellName,
                          Entity* target,
                          float now)
{
    if (now < nextGlobalCooldownEnd)
    {
        std::cout << "[Fail] On Global Cooldown. "
                  << nextGlobalCooldownEnd - now
                  << "s remaining.\n";
        return;
    }

    for (int i = 0; i < abilities.size(); ++i)
    {
        if (abilities[i].getName() == spellName)
        {
            castSpell(target, abilities[i], now);
            return;
        }
    }

    std::cout << "[Fail] Spell not found.\n";
}



void Entity::applyConsumableEffect(const StatModifier& statMod)
{
    // Health buff
    if (statMod.health.has_value()) {
        this->heal(statMod.health.value());
        std::cout << this->getEntityName() << " heals for " << statMod.health.value() << " HP!\n";
        std::cout << this->getEntityName() << " HP: [" << this->getCurrentHP() << "/" << this->getMaxHP() << "]\n";
    }

    // Armor buff
    if (statMod.armor.has_value()) {
        this->getStats().increaseArmor(statMod.armor.value());
        std::cout << this->getEntityName() << " gains " << statMod.armor.value() << " armor!\n";
    }

    // Crit buff
    if (statMod.crit.has_value()) {
        this->getStats().increaseCritChance(statMod.crit.value());
        std::cout << this->getEntityName() << " gains " << statMod.crit.value() << " crit chance!\n";
    }

    // Damage buff
    if (statMod.damage.has_value()) {
        this->getStats().increaseDamage(statMod.damage.value());
        std::cout << this->getEntityName() << " gains +" 
                << statMod.damage.value().first << "-" << statMod.damage.value().second 
                << " damage!\n";
    }
}

bool Entity::tryUseConsumable(const std::string& name, float now)
{
    if (isOnGlobalCooldown(now))
    {
        std::cout << "[Fail] On Global Cooldown. "
                  << getRemainingGCD(now)
                  << "s remaining.\n";
        return false;
    }

    auto const& items =
        inventory->getItemsByType(ITEMTYPE::CONSUMABLE);

    for (auto& it : items)
    {
        if (it->getName() == name)
        {
            std::cout << "[Use] " << name << "\n";

            applyConsumableEffect(it->getStatModifier());
            inventory->removeItem(it);

            setNextGlobalCooldownEnd(now + getGlobalCooldown());
            return true;
        }
    }

    std::cout << "[Fail] Consumable not found.\n";
    return false;
}

void Entity::resolveCast(float now) {
    if (!cast.isCasting || cast.spell == nullptr)
        return;

    Abilities* spell = cast.spell;
    Entity* target = cast.target;

    // finish spell cast
    spell->use(now);

    //Damage spell
    if (spell->isOffensive())
    {
        int dmg = spell->rollDamage();
        if (this->isCrit()) dmg *= 2;

        target->takeDamage(dmg);

        std::cout << this->getEntityName() << " casts "
                    << spell->getName()
                    << " for " << dmg << " damage!\n";
    }
    else if (!(spell->isOffensive()))
    {
        int heal = spell->rollDamage();
        if (this->isCrit()) heal *= 2;

        this->heal(heal);

        std::cout << this->getEntityName() << " casts "
                    << spell->getName()
                    << " that heals themselves for " << heal << "\n";            
    }
    else
    {
        std::cout << this->getEntityName()
                << " finishes casting " << spell->getName() << ".\n";
    }

    
    //trigger gcd
    this->setNextGlobalCooldownEnd(now + this->getGlobalCooldown());

    //Clear cast state
    this->cast.isCasting = false;
    this->cast.spell = nullptr;
    this->cast.target = nullptr;
}


void Entity::update(float now)
{
    if (cast.isCasting && now >= cast.castEnd)
    {
        resolveCast(now);
    }
}

void Entity::takeDamage(const int damage)
{
    float reduction = calcDamageReduction();
    int finalDamage = static_cast<int>(damage * (1.0f - reduction));
    HP.reduceCurrent(finalDamage);
}

void Entity::heal(const int amount)
{
    HP.increaseCurrent(amount);
}

float Entity::calcDamageReduction() const 
{
    float armor = static_cast<float>(stats.getArmor());
    float reduction = armor / (armor + 400.0f + (85.0f * stats.getLevel()));
    return reduction;
}

bool Entity::isOnGlobalCooldown(double now) const {
    return now < nextGlobalCooldownEnd;
}


bool Entity::isCasting() const {
    return cast.isCasting;
}

