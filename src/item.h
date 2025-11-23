#pragma once
#include <cstdint>
#include <random>
#include <iostream>
#include <memory>
#include "statsmod.h"
#include "statblock.h"

enum class ITEMTYPE { WEAPON, ARMOR, CONSUMABLE, MISC }

struct ItemDefinition {
    std::string name;
    int id;
    ITEMTYPE type;
    bool stackable;
    int maxStack;
    StatModifier baseStats;
};

class Item:
{
public:


    Item();
    Item(std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable);

    virtual ~Item();

    const std::string getName();
    const int getID();
    const int getStackSize();
    const bool isStackable();
    const ITEMTYPE getItemType();

    void setName(std::string inName);
    void setID(int inID);
    void setType(ITEMTYPE inType);
    void setStackSize(int inStackSize);
    void setStackable(bool inStackable);

    void incrementStackSize();
    void decrementStackSize();

    bool noMoreStackSize();


    const StatModifier& getStatModifier() const;

    void setDamageBuff(std::pair<int, int> inDamage);

    void setSpeedBuff(float inSpeed);
    void setArmorBuff(int inArmor);

    void setHealthBuff(point_t inHealth);

    [[nodiscard]] std::pair<int, int> getDamageBuff() const;

    [[nodiscard]] float getSpeedBuff() const;

    [[nodiscard]] int getArmorBuff() const;

    [[nodiscard]] point_t getHealthBuff() const;

private:
    std::string name;
    int id;
    ITEMTYPE type;
    int stackSize;
    bool stackable;
    StatModifier statMod;
};
