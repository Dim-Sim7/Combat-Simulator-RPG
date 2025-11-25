#include "armor.h"
#include <cassert>

Armor::Armor() : Item(),  armor(1), durability(1,1) {}

Armor::Armor(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable,
            int inCurrDurability, int inMaxDurability, int inArmor, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot) :
    Item(inName, inId, inType, inStackSize, inStackable), 
    armor(inArmor), armorType(inArmorType), armorSlot(inArmorSlot) 
    { 
        durability.setMax(inMaxDurability);
        durability.setCurrent(inCurrDurability);
    }


void Armor::setCurrDurability(int inCurrDurability)
{
    assert(inCurrDurability >= 0 && "Durability must be 0 or greater");

    durability.setCurrent(inCurrDurability);
}

void Armor::setMaxDurability(int inMaxDurability)
{
    assert(inMaxDurability >= 0 && "Durability must be 0 or greater");

    durability.setMax(inMaxDurability);
}

[[nodiscard]] int Armor::getCurrDurability() const
{
    return durability.getCurrent();
}

[[nodiscard]] int Armor::getMaxDurability() const
{
    return durability.getMax();
}




