#pragma once
#include <cstdint>
#include <random>
#include <iostream>
#include <memory>

#include <optional>
#include <utility>
#include <string>
#include <cassert>
#include "statsmod.h"


class Player;
enum class ITEMTYPE { WEAPON, ARMOR, CONSUMABLE, MISC };

struct ItemDefinition {
    std::string name;
    int id;
    ITEMTYPE type;
    bool stackable;
    int maxStack;
    StatModifier baseStats;
};

class Item {
public:


    Item();
    Item(const std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable);

    virtual ~Item();

    const std::string& getName() const;
    int getID() const;
    int getStackSize() const;
    bool isStackable() const;
    ITEMTYPE getItemType() const;

 
    void setName(const std::string& inName);
    void setID(int inID);
    void setType(ITEMTYPE inType);
    void setStackSize(int inStackSize);
    void setStackable(bool inStackable);

    void incrementStackSize();
    void decrementStackSize();

    bool noMoreStackSize() const;


    const StatModifier& getStatModifier() const;

    void setDamageBuff(std::pair<int, int> inDamage);

    void setSpeedBuff(float inSpeed);
    void setArmorBuff(int inArmor);

    void setHealthBuff(int inHealth);

    [[nodiscard]] std::pair<int,int> getDamageBuff() const;

    [[nodiscard]] std::optional<float> getSpeedBuff() const;

    [[nodiscard]] std::optional<int> getArmorBuff() const;

    [[nodiscard]] std::optional<int> getHealthBuff() const;


private:
    std::string name;
    int id;
    ITEMTYPE type;
    int stackSize;
    bool stackable;
    StatModifier statMod;
};
