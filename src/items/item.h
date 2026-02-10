#pragma once
#include <cstdint>
#include <random>
#include <iostream>
#include <memory>

#include <optional>
#include <utility>
#include <string>
#include <cassert>
#include "../items/definitions/statsmod.h"
#include "definitions/item_def.h"

class Player;
enum class ITEMTYPE { WEAPON, ARMOR, CONSUMABLE, MISC };
enum class Rarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary
};

class Item {
public:


    Item();
    Item(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable);

    virtual ~Item() = default;

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
    void setCritBuff(float inCrit);

    [[nodiscard]] std::pair<int,int> getDamageBuff() const;

    [[nodiscard]] std::optional<float> getSpeedBuff() const;

    [[nodiscard]] std::optional<int> getArmorBuff() const;

    [[nodiscard]] std::optional<int> getHealthBuff() const;

    [[nodiscard]] std::optional<float> getCritBuff() const;
    
    void setRarity(const Rarity& rarity);
    Rarity rarity() const;

protected:
    std::string name_;
    int id_;
    ITEMTYPE type_;
    int stackSize_;
    bool stackable_;

    StatModifier statMod_;
    Rarity rarity_;
};
