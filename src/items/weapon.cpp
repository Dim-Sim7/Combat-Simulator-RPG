
#include "weapon.h"


Weapon::Weapon(): Item() {}

Weapon::Weapon(std::string inName, int inId, int minDamage, int maxDamage, float speed, WEAPONTYPE weaponType)
    : Item(std::move(inName), inId, ItemType::Weapon, 1, false),
            weaponType_(weaponType), minDamage_(minDamage), maxDamage_(maxDamage), speed_(speed)
    {}


[[nodiscard]] bool Weapon::isTwoHanded()
{
    switch (weaponType_) {
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
    return weaponType_;
}



