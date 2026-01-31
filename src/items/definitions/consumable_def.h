#pragma once
#include "statsmod.h"
enum class CONSUMABLETYPE { POTION, BUFF, THROWABLE, POISON, ELIXIR, KEY, QUEST };

struct ConsumableDef {
    int consumable_id;
    int stack_size;
    bool stackable;
    float duration;
    StatModifier statMod;
    CONSUMABLETYPE consumable_type;
};