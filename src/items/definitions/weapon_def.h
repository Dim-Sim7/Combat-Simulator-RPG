#pragma once

enum class WEAPONTYPE {DAGGER, FIST_WEAPON, ONE_HAND_AXE, ONE_HAND_MACE, ONE_HAND_SWORD, POLEARM, STAVE, TWO_HAND_AXE, TWO_HAND_MACE, TWO_HAND_SWORD,
                        BOW, CROSSBOW, GUN, THROWN, WAND};

struct WeaponDef {
    int weapon_id;
    int minDamage;
    int maxDamage;
    float speed;
    WEAPONTYPE type;
};