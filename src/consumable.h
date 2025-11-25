#pragma once
#include "item.h"
#include <cassert>

//A consumable affects the player's stats. Increasing health, damage, armor.
class Consumable: public Item {

public:
    Consumable();

    Consumable(std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, float inDuration);
    void setDuration(float inDuration);
    void use();
    [[nodiscard]] float getDuration() const;


private:
    float duration;

};
