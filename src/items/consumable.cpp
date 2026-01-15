
#include "consumable.h"


Consumable::Consumable(): Item(), duration(0.0f) {}

Consumable::Consumable(std::string inName, int inId, int inStackSize, bool inStackable, 
                        float inDuration, CONSUMABLETYPE inConsumableType):
    Item(std::move(inName), inId, ITEMTYPE::CONSUMABLE, inStackSize, inStackable), 
    duration(inDuration), consumableType(inConsumableType) {}

void Consumable::setDuration(float inDuration)
{
    assert(inDuration >= 0.0f && "Duration cannot be negative");

    if (inDuration < 0.0f)
    {
        inDuration = 0.0f;
    }

    duration = inDuration;
}

[[nodiscard]] float Consumable::getDuration() const
{
    return duration;
}

void Consumable::use()
{
    Item::decrementStackSize();
}
