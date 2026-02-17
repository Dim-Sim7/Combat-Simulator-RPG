#pragma once

#include "entity.h"
#include <memory>
#include <vector>
#include <string>


class Item;
class Inventory;
class EquipSlots;
class Abilities;
class AbilitiesPool;
class StatBlock;

//player class. Handles playable character. Attacking, cast spells, leveling, death
class Player: public Entity {

public:    

    Player();

    Player(const StatBlock& statsInit, 
        const int hpInitCurr, 
        const int hpInitMax, 
        const std::vector<Abilities>& abilitiesInit,
        const std::string& nameInit);
    
    void gainExp(int earnedEXP);


    void onDeath() override;
    
    bool equipItem(Item& item);

private:
    PointWell EXP;
    //Handle item equip logic
    bool equipWeapon(Item& itemToEquip);
    bool equipArmor(Item& itemToEquip);
    void recalculateStats();
    void levelUp();
    int getEXPToLevel();



    

};
