#include "armor.h"

Armor::Armor() : Item(), durability(0) {}

Armor::Armor(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, int inDurability, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot) :
    Item(inName, inId, inType, inStackSize, inStackable), durability(inDurability), armorType(inArmorType), armorSlot(inArmorSlot) {}


void Armor::setDurability(int inDurability)
{
    assert(inDurability >= 0 && "Durability must be 0 or greater");

    if (inDurability < 0)
    {
        inDurability = 0;
    }

    durability = inDurability;
}

[[no discard]] int Armor::getDurability() const
{
    return durability;
}


