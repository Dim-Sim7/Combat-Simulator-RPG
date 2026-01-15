#pragma once

#include <cstdint>
#include <utility>
#include "item.h"
#include "./definitions/weapon_def.h"
class StatBlock;

class Weapon : public Item {

public:
    Weapon();

    Weapon(std::string inName, int inId, int minDamage, int maxDamage, float speed, WEAPONTYPE weaponType);
        
    [[nodiscard]] inline bool isTwoHanded();

    WEAPONTYPE getWeaponType() const;

    
private:
    WEAPONTYPE weaponType_;
    int minDamage_;
    int maxDamage_;
    float speed_;

};
