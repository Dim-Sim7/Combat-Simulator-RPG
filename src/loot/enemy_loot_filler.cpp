#include "enemy_loot_filler.h"


void EnemyLootFiller::fill(Container& container, const LootContext& ctx) const {
    rollGold(container, ctx);
    rollItems(container, ctx);
}


void EnemyLootFiller::rollGold(Container& container, const LootContext& ctx) const {
    float base = ctx.level * 0.6f;
    float variance = ctx.rng.randomFloat(0.7f, 1.3f);

    float multiplier = 1.0f;

    // Scale by enemy tier
    multiplier *= tierScale(ctx.enemyTier);

    // Optional chest bonus
    if (ctx.chestTier.has_value()) {
        multiplier *= (1.0f + (*ctx.chestTier * 0.1f));
    }

    int amt = static_cast<int>(std::round(base * variance * multiplier));
    container.add<Gold>(amt);
}


//constructs loot table based on enemy context, items are randomly rolled within that table and added to container
//create the items
void EnemyLootFiller::rollItems(Container& container, const LootContext& ctx) const {
    Table t{ctx};
    container.add(t.getLoot);
}
