#pragma once

#include "entity.h"
#include <cstdint>
#include <random>
#include <cmath>
#include <vector>
#include <memory>
#include <cassert>
#include <utility>
#include <array>
#include <optional>
#include "equipslots.h"
#include "abilities_pool.h"
#include "inventory.h"

class Item;
class Inventory;
class EquipSlots;
class Abilities;
class AbilitiesPool;
class StatBlock;

//player class. Handles playable character. Attacking, cast spells, leveling, death
class Player: public Entity {

public:    
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<EquipSlots> equipSlots;
    std::unique_ptr<AbilitiesPool> aPool;
    ~Player();
    Player();

    Player(const StatBlock& statsInit, 
        const int& hpInitCurr, 
        const int& hpInitMax, 
        const std::vector<Abilities>& abilitiesInit,
        const std::string& nameInit);
    
    void gainExp(int earnedEXP);


    void onDeath();


private:
    PointWell EXP;
    


    //Handle item equip logic
    void equipWeapon(Item& itemToEquip);

    //IMPLEMENT
    void recalculateStats();

    void levelUp();

    int getEXPToLevel();

    

};
