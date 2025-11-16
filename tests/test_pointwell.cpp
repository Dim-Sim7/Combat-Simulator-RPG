#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../src/pointwell.h"

TEST_CASE("POINTWELL INITIALISATION", "[PointWell]")
{
    PointWell p;
    REQUIRE(p.getCurrent() == 1);
    REQUIRE(p.getMax() == 1);
}

TEST_CASE("POINTWELL PARAMETER CONSTRUCTION", "[PointWell]")
{
    PointWell p(100, 80);
    REQUIRE(p.getCurrent() == 80);
    REQUIRE(p.getMax() == 100);
}

TEST_CASE("Increase Max")
{
    PointWell p(100, 100);
    p.setMax(300);
    REQUIRE(p.getMax() == 300);
    REQUIRE(p.getCurrent() == 100);
}

TEST_CASE("Increase Current")
{
    PointWell p(100, 80);
    p.increaseCurrent(20);
    REQUIRE(p.getCurrent() == 100);
}

TEST_CASE("Increase Current Past Max")
{
    PointWell p(100, 80);
    p.increaseCurrent(40);
    REQUIRE(p.getCurrent() == 100);
}

TEST_CASE("reduce Current")
{
    PointWell p(100, 80);
    p.reduceCurrent(20);
    REQUIRE(p.getCurrent() == 60);
}

TEST_CASE("Set max below current")
{
    PointWell p(100, 80);
    p.setMax(20);
    REQUIRE(p.getMax() == 20);
    REQUIRE(p.getCurrent() == 20);
}
