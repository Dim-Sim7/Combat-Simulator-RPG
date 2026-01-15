#pragma once

//Given container context, this class will fill loot to the required container
//Need to know about container level, container type
#include "gold.h"
#include "lootable_item.h"
#include "rng.cpp"
#include <random>


class EnemyLootFiller final : public LootFiller {
public:
    void fill(Container& container, const LootContext& ctx) const override {
        rollGold(container, ctx);
        rollItems(container, ctx);
    }

private:
    void rollGold(Container& container, const LootContext& ctx) {
        float base = ctx.level * 0.6f;
        float variance = RNG::randomFloat(0.7f, 1.3f);

        float multiplier = 1.0f;
        if (ctx.isElite) multiplier *= 2.0f;
        if (ctx.isDungeon) multiplier *= 1.2f;
        if (ctx.mobType == MobType::Humanoid)
            multiplier *= 1.1f;
        
        int amt = (static_cast<int>(std::round(base * variance * multiplier)));    
        container.add<Gold>(amt);

    }

    //constructs loot table based on enemy context, items are randomly rolled within that table and added to container
    //create the items
    void rollItems(Container& container, const LootContext& ctx) {
        Table t{ctx};
        container.add(t.getLoot);
    }
};