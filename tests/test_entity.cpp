#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../src/entity.h"

Entity makeEntityWithParameters() {
    StatBlock sb({10, 20}, 10, 1);
    PointWell p(100, 80);
    std::vector<Abilities> abilities;
    
    Entity e(sb, p.getCurrent(), p.getMax(), abilities, "MIKE");

    e.addAbility(Abilities("Fireball", std::make_pair(100u, 150u), 3, 2, 50, ability_t::CAST));
    return e;
}

TEST_CASE("Default Constructor - Entity")
{
    Entity e;
    REQUIRE(e.getEntityName() == "");
    REQUIRE(e.getHP().getCurrent() == 1);
}

TEST_CASE("Parameter Constructor - Entity")
{
    StatBlock sb({10, 20}, 10, 1);
    PointWell p(100, 80);
    std::vector<Abilities> abilities;
    
    Entity e(sb, p.getCurrent(), p.getMax(), abilities, "MIKE");

    e.addAbility(Abilities("Fireball", std::make_pair(100u, 150u), 3, 2, 50, ability_t::CAST));

    REQUIRE(e.getEntityName() == "MIKE");
    REQUIRE(e.getHP().getCurrent() == 80);
    REQUIRE(e.getHP().getMax() == 100);
    const std::vector<Abilities> eAbilities = e.getAbilities();
    REQUIRE(eAbilities[0].getName() == "Fireball");
    REQUIRE(eAbilities[0].getAmountRange().first == 100u);
    REQUIRE(eAbilities[0].getAmountRange().second == 150u);
    REQUIRE(eAbilities[0].rollDamage() <= 150);
    REQUIRE(eAbilities[0].getType() == ability_t::CAST);
}

TEST_CASE("isDead Returns False (entity is alive)")
{
    auto e = makeEntityWithParameters();

    REQUIRE_FALSE(e.isDead());
}

TEST_CASE("isDead Returns True (entity is dead)")
{
    auto e = makeEntityWithParameters();
    e.getHP().setCurrent(0u);
    REQUIRE(e.isDead());
}
