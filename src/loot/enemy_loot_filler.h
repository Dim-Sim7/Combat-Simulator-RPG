#pragma once

//Given container context, this class will fill loot to the required container
//Need to know about container level, container type
#include "gold.h"
#include "loot_filler.h"
#include "rng.h"
#include "container.h"
#include "loot_context.h"
#include <random>
#include "table.h"


class EnemyLootFiller final : public LootFiller {
public:
    void fill(Container& container, const LootContext& ctx) const override;
private:
    void rollGold(Container& container, const LootContext& ctx) const;

    //constructs loot table based on enemy context, items are randomly rolled within that table and added to container
    //create the items
    void rollItems(Container& container, const LootContext& ctx) const;
};