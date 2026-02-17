#include <catch2/catch_test_macros.hpp>

#include "lootable_value.h"

TEST_CASE("LootableValue default constructor", "[loot][value]")
{
    LootableValue v;

    REQUIRE(v.amount() == 0);
    REQUIRE(v.weight() == 0);
    REQUIRE_FALSE(v.isUnique());
    REQUIRE_FALSE(v.isAlways());
}

TEST_CASE("LootableValue setters and getters", "[loot][value]")
{
    LootableValue v(10, 5, true, false);

    REQUIRE(v.amount() == 10);
    REQUIRE(v.weight() == 5);
    REQUIRE(v.isUnique());
    REQUIRE_FALSE(v.isAlways());

    v.setAmount(20);
    v.setWeight(7);
    v.setUnique(false);
    v.setAlways(true);

    REQUIRE(v.amount() == 20);
    REQUIRE(v.weight() == 7);
    REQUIRE_FALSE(v.isUnique());
    REQUIRE(v.isAlways());
}
