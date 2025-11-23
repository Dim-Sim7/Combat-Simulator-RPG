
#include "consumable.h"


Consumable::Consumable(): Item(), duration(0.0f) {}

Consumable::Consumable(std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, float inDuration) :
    Item(inName, inId, inType, inStackSize, inStackable), duration(inDuration) {}

void Consumable::setDuration(float inDuration)
{
    assert(inDuration >= 0.0f && "Duration cannot be negative");

    if (inDuration < 0.0f)
    {
        inDuration = 0.0f;
    }

    duration = inDuration;
}


[[nodiscard]] float getDuration() const
{
    return duration;
}

void Consumable::use()
{
    Item::decrementStackSize();
}
