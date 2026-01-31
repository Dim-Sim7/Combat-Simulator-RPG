#pragma once

//Interface for filling loot. Provides function interface for any future loot filler
#include "loot_context.h"
class LootFiller {
public:
    virtual ~LootFiller() = default;

    virtual void fill(Container& container, const LootContext% ctx) const = 0;
};