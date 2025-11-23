#pragma once

#include "item.h"
#include "weapon.h"
//Represents an equipslot for a player's character sheet
//an equip slot can either be a weapon or armour slots (might be expanded later)
//if an item is in an equipslot, it modifies the player's stats
//how to represent equipslot? an array of items that has an enum class
enum EQUIP_SLOT_TYPE {MAIN_HAND, OFF_HAND, CHEST, FEET, HANDS, HEAD, LEGS, SHOULDER, WAIST, WRIST, CLOAK, SHIELD, COUNT}
class EquipSlots
{
public:
    EquipSlots() {}

    void equipItem(Item& itemToEquip, EQUIP_SLOT_TYPE equipSlot)
    {
        equipSlotArray[equipSlot] = &itemToEquip;
    }

    void unequipItem(EQUIP_SLOT_TYPE equipSlot)
    {
        equipSlotArray[equipSlot] = nullptr;
    }

    StatModifier getTotalStatMods()
    {
        StatModifier totalStatMod;
        for (auto& item : equipSlotArray)
        {
            if (item)
                totalStatMod += item->getStatModifier();
        }

        return totalStatMod;
    }

    bool isSlotEquipped(EQUIP_SLOT_TYPE equipSlot)
    {
        return equipSlotArray[equipSlot];
    }

    Item* getItemFromSlot(EQUIP_SLOT_TYPE equipSlot)
    {
        return equipSlotArray[equipSlot];
    }

private:
    std::array<Item*, EQUIP_SLOT_TYPE::COUNT> equipSlotArray;



};
