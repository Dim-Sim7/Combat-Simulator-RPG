#pragma once
#include "pointwell.h"
#include "statblock.h"
#include "../abilities/abilities.h"
#include "../abilities/abilities_pool.h"
#include <string>
#include "../items/item.h"
#include <memory>
#include <vector>
#include <random>
#include "../items/equipslots.h"
#include "../items/inventory.h"
class Entity; //forward declaration
struct CastState {
    bool isCasting = false;
    float castStart{0.0f};
    float castEnd{0.0f};
    Abilities* spell = nullptr;
    Entity* target = nullptr;
};
    
class Inventory;
class EquipSlots;
/**
 * @brief Entity represents either a player or NPC.
 * Provides virtual methods to be implemented by children
 * has implemented methods that are the same regardless of children
 */
class Entity {
public:
    Entity();
    explicit Entity(const StatBlock& statsInit, 
        const int hpInitCurr, 
        const int hpInitMax, 
        const std::vector<Abilities>& abilitiesInit,
        const std::string& inName);
    virtual ~Entity() = default;

   

    StatBlock& getStats();
    PointWell& getHP();
    std::vector<Abilities>& getAbilities();

    const StatBlock& getStats() const; //const after states that this method cannot modify member variables in general
    const PointWell& getHP() const; //const before states that I will not modify the thing being called. Const after is added to differentiate to the compiler the other non-const getters
    const std::vector<Abilities>& getAbilities() const;

    int getMaxHP() const;
    int getCurrentHP() const;
    Inventory* getInventory();
    const Inventory* getInventory() const;

    void setStats(StatBlock inStats);
    void setHP(PointWell inHP);
    void setAbilities(std::vector<Abilities> inAbilities);

    bool isDead() const;
    bool isCrit() const;
    bool isCasting() const;

    virtual void onDeath() = 0;

    void addAbility(const Abilities& ability);

    std::string getEntityName() const;
    void setEntityName(const std::string& inName);
    
    void attack(Entity& target, float currentTime);
    void castSpell(Entity* target, Abilities& spell, float currentTime);
    void tryCastSpell(const std::string& spellName, Entity* target, float now);

    void applyConsumableEffect(const StatModifier& statMod);
    bool tryUseConsumable(const std::string& name, float now);

    void resolveCast(float now);
    void update(float now);

    void takeDamage(const int damage);
    float calcDamageReduction() const;
    void heal(const int amount);

    double getNextAutoAttackTime() const;
    void setNextAutoAttackTime(double t);

    double getNextGlobalCooldownEnd() const;
    void setNextGlobalCooldownEnd(double t);

    double getAttackSpeed() const;
    double getGlobalCooldown() const;
    bool isOnGlobalCooldown(double now) const;




protected:
    StatBlock stats;
    PointWell HP; 
    std::vector<Abilities> abilities;
    std::string name;
     
    CastState cast;

    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<EquipSlots> equipSlots;
    std::unique_ptr<AbilitiesPool> aPool;
    
    double nextAutoAttackTime{0.0};
    double nextGlobalCooldownEnd{0.0};
    double attackSpeed{2.6}; // default attack speed
    double globalCooldown{1.5}; // standard GCD
};
