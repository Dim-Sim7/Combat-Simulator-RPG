#pragma once

enum class ARMORTYPE {CLOTH, LEATHER, MAIL, PLATE, CLOAK, SHIELD};
enum class ARMORSLOT {CHEST, FEET, HANDS, HEAD, LEGS, SHOULDER, WAIST, WRIST, CLOAK, SHIELD};

struct ArmorDef {
    int armor_id;
    int armor;
    int maxDurability;
    ARMORTYPE armorType;
    ARMORSLOT armorSlot;
};