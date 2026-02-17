#include <catch2/catch_test_macros.hpp>

#include "enemy_loot_filler.h"
#include "loot_context.h"
#include "container.h"
#include "gold.h"

TEST_CASE("EnemyLootFiller adds gold", "[loot][enemy]")
{
    LootContext ctx;
    ctx.level = 10;
    ctx.isElite = false;
    ctx.isDungeon = false;
    ctx.mobType = MobType::Beast;

    Container container;
    EnemyLootFiller filler;

    filler.fill(container, ctx);

    auto gold = container.get<Gold>();
    REQUIRE(gold.has_value());
    REQUIRE(gold->amount() > 0);
}

TEST_CASE("Elite enemies drop more gold", "[loot][enemy]")
{
    LootContext normal;
    normal.level = 10;
    normal.isElite = false;

    LootContext elite = normal;
    elite.isElite = true;

    Container c1, c2;
    EnemyLootFiller filler;

    filler.fill(c1, normal);
    filler.fill(c2, elite);

    REQUIRE(c2.get<Gold>()->amount() > c1.get<Gold>()->amount());
}
