
#include "weapon.h"


Weapon::Weapon(): Item() {}

Weapon::Weapon(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, WEAPONTYPE inWeaponType, std::pair<int, int> inDmg, float inSpeed):
    Item(inName, inId, inType, inStackSize, inStackable), weaponType(inWeaponType) //ITEM PARAMETER CONSTRUCTOR
    {
        statMod.damage = inDmg;
        statMod.speed = inSpeed;
    }

[[nodiscard]] inline bool Weapon::isTwoHanded()
{
    switch (weaponType) {
        case WEAPONTYPE::TWO_HAND_AXE:
        case WEAPONTYPE::TWO_HAND_MACE:
        case WEAPONTYPE::TWO_HAND_SWORD:
        case WEAPONTYPE::BOW:
        case WEAPONTYPE::CROSSBOW:
        case WEAPONTYPE::GUN:
        case WEAPONTYPE::POLEARM:
        case WEAPONTYPE::STAVE:
            return true;
        default:
            return false;
    }
}

WEAPONTYPE const Weapon::getWeaponType()
{
    return weaponType;
}



