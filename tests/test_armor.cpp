#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "item.h"
#include "armor.h"
#include "weapon.h"
#include <cassert>

TEST_CASE("Item stat modifiers work correctly", "[Item]") {

    std::string name = "Rusty Sword";
    Item sword(name, 1, ITEMTYPE::WEAPON, 1, false);

    // Apply stats
    sword.setDamageBuff({2, 5});
    sword.setSpeedBuff(1.25f);
    sword.setArmorBuff(3);
    sword.setHealthBuff(10);

    SECTION("Damage modifier set") {
        auto dmg = sword.getDamageBuff();
        REQUIRE(sword.getDamageBuff()->first == 2);
        REQUIRE(sword.getDamageBuff()->second == 5);
    }

    SECTION("Speed modifier set") {
        REQUIRE(sword.getSpeedBuff() == Catch::Approx(1.25f));
    }

    SECTION("Armor modifier set") {
        REQUIRE(sword.getArmorBuff() == 3);
    }

    SECTION("Health modifier set") {
        REQUIRE(sword.getHealthBuff() == 10);
    }
}

TEST_CASE("Armor attributes work correctly", "[Armor]") {

    std::string name = "Iron Chestplate";
    Armor chest(
        name,
        2,
        ITEMTYPE::ARMOR,
        1,
        false,
        50,      // current durability
        100,     // max durability
        20,      // armor
        ARMORTYPE::PLATE,
        ARMORSLOT::CHEST
    );

    SECTION("Durability initialized correctly") {
        REQUIRE(chest.getCurrDurability() == 50);
        REQUIRE(chest.getMaxDurability() == 100);
    }

    SECTION("Durability updates correctly") {
        chest.setCurrDurability(30);
        REQUIRE(chest.getCurrDurability() == 30);

        chest.setMaxDurability(120);
        REQUIRE(chest.getMaxDurability() == 120);
    }

    SECTION("Armor buff applies") {
        chest.setArmorBuff(8);
        REQUIRE(chest.getArmorBuff() == 8);
    }
}
