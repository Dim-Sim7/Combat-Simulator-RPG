#pragma once
#include <array>
#include <cstddef>
#include "statsmod.h"

//Represents an equipslot for a player's character sheet
//an equip slot can either be a weapon or armour slots (might be expanded later)
//if an item is in an equipslot, it modifies the player's stats
//how to represent equipslot? an array of items that has an enum class

class Item;

enum class EQUIP_SLOT_TYPE {MAIN_HAND, OFF_HAND, CHEST, FEET, HANDS, HEAD, LEGS, SHOULDER, WAIST, WRIST, CLOAK, SHIELD, COUNT};
class EquipSlots
{
public:
    EquipSlots();

    void equipItem(Item& itemToEquip, EQUIP_SLOT_TYPE equipSlot);
    void unequipItem(EQUIP_SLOT_TYPE equipSlot);
    StatModifier getTotalStatMods();
    bool isSlotEquipped(EQUIP_SLOT_TYPE equipSlot);

    Item* getItemFromSlot(EQUIP_SLOT_TYPE equipSlot);

private:
    std::array<Item*, static_cast<size_t>(EQUIP_SLOT_TYPE::COUNT)> equipSlotArray;



};
