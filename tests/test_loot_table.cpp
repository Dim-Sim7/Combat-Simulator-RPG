#include <catch2/catch_test_macros.hpp>
#include <fstream>

#include "loot_table.h"
#include "loot_context.h"
#include "rng.h"

static void writeTestCSV(const std::string& path)
{
    std::ofstream file(path);
    file << "itemId,minLevel,maxLevel,baseWeight,bossOnly\n";
    file << "1,1,10,10,false\n";
    file << "2,1,10,5,false\n";
    file << "3,5,20,20,true\n";
}

TEST_CASE("LootTable filters by level and boss", "[loot][table]")
{
    const std::string csv = "test_loot.csv";
    writeTestCSV(csv);

    LootContext ctx;
    ctx.level = 3;
    ctx.encounterType = EncounterType::Normal;

    LootTable table(ctx, csv);
    auto rolls = table.rollItemIds();

    REQUIRE_FALSE(rolls.empty());

    for (int id : rolls) {
        REQUIRE(id != 3); // boss-only item
    }
}

TEST_CASE("LootTable allows boss-only items for bosses", "[loot][table]")
{
    const std::string csv = "test_loot.csv";
    writeTestCSV(csv);

    LootContext ctx;
    ctx.level = 10;
    ctx.encounterType = EncounterType::Boss;

    LootTable table(ctx, csv);
    auto rolls = table.rollItemIds();

    bool foundBossItem = false;
    for (int id : rolls) {
        if (id == 3)
            foundBossItem = true;
    }

    REQUIRE(foundBossItem);
}
