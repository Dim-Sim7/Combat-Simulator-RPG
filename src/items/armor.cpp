#include "armor.h"
#include <cassert>

Armor::Armor() : Item(),  armor_(1), durability(1,1) {}

Armor::Armor(std::string inName, int inId,
            int inCurrDurability, int inMaxDurability, 
            int inArmor, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot) :
    Item(std::move(inName), inId, ITEMTYPE::ARMOR, 1, false), 
    armor_(inArmor), armorType_(inArmorType), armorSlot_(inArmorSlot) 
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




