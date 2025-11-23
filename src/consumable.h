#pragma once

//A consumable affects the player's stats. Increasing health, damage, armor.
class Consumable: public Item {

public:
    Consumable(): Item(), duration(0.0f) {}

    Consumable(std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable, float inDuration) :
        Item(inName, inId, inType, inStackSize, inStackable), duration(inDuration) {}
    
    void setDuration(float inDuration)
    {
        assert(inDuration >= 0.0f && "Duration cannot be negative");

        if (inDuration < 0.0f)
        {
            inDuration = 0.0f;
        }

        duration = inDuration;
    }

    void use()
    {
        Item::decrementStackSize();
    }

    [[nodiscard]] float getDuration() const;


private:
    float duration;

};
