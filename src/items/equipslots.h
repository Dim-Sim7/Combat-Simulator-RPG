#pragma once
#include <array>
#include <cstddef>
#include <stdexcept>
#include "../items/definitions/statsmod.h"
#include "definitions/armor_def.h"


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

    
    constexpr EQUIP_SLOT_TYPE toEquipSlot(ARMORSLOT slot) {
        switch(slot) {
            case ARMORSLOT::CHEST: return EQUIP_SLOT_TYPE::CHEST;
            case ARMORSLOT::FEET: return EQUIP_SLOT_TYPE::FEET;
            case ARMORSLOT::HANDS: return EQUIP_SLOT_TYPE::HANDS;
            case ARMORSLOT::HEAD: return EQUIP_SLOT_TYPE::HEAD;
            case ARMORSLOT::LEGS: return EQUIP_SLOT_TYPE::LEGS;
            case ARMORSLOT::SHOULDER: return EQUIP_SLOT_TYPE::SHOULDER;
            case ARMORSLOT::WAIST: return EQUIP_SLOT_TYPE::WAIST;
            case ARMORSLOT::CLOAK: return EQUIP_SLOT_TYPE::CLOAK;
            case ARMORSLOT::SHIELD: return EQUIP_SLOT_TYPE::SHIELD;
        }

        throw std::logic_error("Invalid ArmorSlot");
    }

private:
    std::array<Item*, static_cast<size_t>(EQUIP_SLOT_TYPE::COUNT)> equipSlotArray;

};
