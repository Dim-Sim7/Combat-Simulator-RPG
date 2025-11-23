#pragma once

#include <cstdint>
#include <utility>
#include "statblock.h"

enum class WEAPONTYPE {DAGGER, FIST_WEAPON, ONE_HAND_AXE, ONE_HAND_MACE, ONE_HAND_SWORD, POLEARM, STAVE, TWO_HAND_AXE, TWO_HAND_MACE, TWO_HAND_SWORD,
                        BOW, CROSSBOW, GUN, THROWN, WAND}
class Weapon : public Item {

public:
    Weapon();

    Weapon(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, WEAPONTYPE inWeaponType, std::pair<int, int> inDmg, float inSpeed);

    [[nodiscard]] inline bool isTwoHanded();

    WEAPONTYPE const getWeaponType();

private:
    WEAPONTYPE weaponType;

};
