#pragma once
#include <cstdint>

enum class ARMORTYPE {CLOTH, LEATHER, MAIL, PLATE, CLOAK, SHIELD}
enum class ARMORSLOT {CHEST, FEET, HANDS, HEAD, LEGS, SHOULDER, WAIST, WRIST, CLOAK, SHIELD}

class Armor: public Item {
public:
    Armor() : Item(), durability(0) {}

    Armor(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, int inDurability, ARMORTYPE inArmorType, ARMORSLOT inArmorSlot) :
        Item(inName, inId, inType, inStackSize, inStackable), durability(inDurability), armorType(inArmorType), armorSlot(inArmorSlot) {}


    void setDurability(int inDurability)
    {
        assert(inDurability >= 0 && "Durability must be 0 or greater");

        if (inDurability < 0)
        {
            inDurability = 0;
        }

        durability = inDurability;
    }

    [[no discard]] int getDurability() const
    {
        return durability;
    }

private:
    int durability;
    ARMORTYPE armorType;
    ARMORSLOT armorSlot;

};
