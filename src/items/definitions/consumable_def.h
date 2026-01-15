#pragma once
#include "statsmod.h"
enum class CONSUMABLETYPE { POTION, THROWING, KEY, QUEST };

struct ConsumableDef {
    int consumable_id;
    int stack_size;
    bool stackable;
    float duration;
    CONSUMABLETYPE consumable_type;
    StatModifier statMod;
};