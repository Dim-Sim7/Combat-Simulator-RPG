
#include "weapon.h"


Weapon::Weapon(): Item() {}

Weapon::Weapon(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, WEAPONTYPE inWeaponType):
    Item(inName, inId, inType, inStackSize, inStackable), weaponType(inWeaponType) //ITEM PARAMETER CONSTRUCTOR
    {

    }

[[nodiscard]] bool Weapon::isTwoHanded()
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

WEAPONTYPE Weapon::getWeaponType() const
{
    return weaponType;
}



