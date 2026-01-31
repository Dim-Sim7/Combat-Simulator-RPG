#include "enemy_loot_filler.h"


void EnemyLootFiller::fill(Container& container, const LootContext& ctx) const override {
    rollGold(container, ctx);
    rollItems(container, ctx);
}


void EnemyLootFiller::rollGold(Container& container, const LootContext& ctx) {
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
void EnemyLootFiller::rollItems(Container& container, const LootContext& ctx) {
    Table t{ctx};
    container.add(t.getLoot);
}
