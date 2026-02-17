#pragma once
#include "item.h"
#include "definitions/statsmod.h"
#include "definitions/consumable_def.h"
#include <cassert>

//A consumable affects the player's stats. Increasing health, damage, armor.
class Consumable: public Item {

public:
    Consumable();

    Consumable(std::string inName, int inId, int inStackSize, bool inStackable, 
        float inDuration, CONSUMABLETYPE inConsumableType);
    void setDuration(float inDuration);
    void use();
    [[nodiscard]] float getDuration() const;


private:
    float duration;
    CONSUMABLETYPE consumableType;

};
