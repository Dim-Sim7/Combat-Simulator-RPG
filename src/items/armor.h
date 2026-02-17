#pragma once
#include <cstdint>
#include "item.h"
#include "../entities/pointwell.h"
#include "definitions/armor_def.h"


class Armor: public Item {
public:
    Armor();

    Armor(std::string inName, int inId, 
            int inCurrDurability, int inMaxDurability, 
            int inArmor, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot);

    void setCurrDurability(int inCurrDurability);
    void setMaxDurability(int inDurability);
    [[nodiscard]] int getCurrDurability() const;
    [[nodiscard]] int getMaxDurability() const;

    ARMORTYPE armorType() {
        return armorType_;
    }

    ARMORSLOT armorSlot() {
        return armorSlot_;
    }
    
private:
    int armor_;
    PointWell durability;
    ARMORTYPE armorType_;
    ARMORSLOT armorSlot_;

};
