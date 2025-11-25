#pragma once
#include <cstdint>
#include "item.h"
#include "pointwell.h"

class PointWell;

enum class ARMORTYPE {CLOTH, LEATHER, MAIL, PLATE, CLOAK, SHIELD};
enum class ARMORSLOT {CHEST, FEET, HANDS, HEAD, LEGS, SHOULDER, WAIST, WRIST, CLOAK, SHIELD};

class Armor: public Item {
public:
    Armor();

    Armor(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, int inCurrDurability, int inMaxDurability, 
            int inArmor, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot);

    void setCurrDurability(int inCurrDurability);
    void setMaxDurability(int inDurability);
    [[nodiscard]] int getCurrDurability() const;
    [[nodiscard]] int getMaxDurability() const;

private:
    int armor;
    PointWell durability;
    ARMORTYPE armorType;
    ARMORSLOT armorSlot;

};
