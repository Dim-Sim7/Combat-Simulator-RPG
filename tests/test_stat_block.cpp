#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../src/statblock.h"

TEST_CASE("StatBlock initialization", "[StatBlock]") {
    StatBlock sb({10, 20}, 5, 1);
    REQUIRE(sb.getDamageRange().first == 10);
    REQUIRE(sb.getDamageRange().second == 20);
    REQUIRE(sb.getArmor() == 5);
    REQUIRE(sb.getLevel() == 1);
}

TEST_CASE("Level up increases stats", "[StatBlock]") {
    StatBlock sb({10, 20}, 10, 1);
    sb.levelUp();
    REQUIRE(sb.getLevel() == 2);
    REQUIRE(sb.getArmor() > 10);
    REQUIRE(sb.getDamageRange().first > 10);
}
