#include "equipslots.h"
#include "item.h"
//Represents an equipslot for a player's character sheet
//an equip slot can either be a weapon or armour slots (might be expanded later)
//if an item is in an equipslot, it modifies the player's stats
//how to represent equipslot? an array of items that has an enum class

EquipSlots::EquipSlots() {}

void EquipSlots::equipItem(Item& itemToEquip, EQUIP_SLOT_TYPE equipSlot)
{
    equipSlotArray[static_cast<size_t>(equipSlot)] = &itemToEquip;
}

void EquipSlots::unequipItem(EQUIP_SLOT_TYPE equipSlot)
{
    equipSlotArray[static_cast<size_t>(equipSlot)] = nullptr;
}

StatModifier EquipSlots::getTotalStatMods()
{
    StatModifier totalStatMod;
    for (auto& item : equipSlotArray)
    {
        if (item)
            totalStatMod = totalStatMod + item->getStatModifier();
    }

    return totalStatMod;
}

bool EquipSlots::isSlotEquipped(EQUIP_SLOT_TYPE equipSlot)
{
    return equipSlotArray[static_cast<size_t>(equipSlot)] != nullptr;
}

Item* EquipSlots::getItemFromSlot(EQUIP_SLOT_TYPE equipSlot)
{
    return equipSlotArray[static_cast<size_t>(equipSlot)];
}

