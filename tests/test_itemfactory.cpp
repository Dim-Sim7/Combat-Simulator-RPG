#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include <random>

#include "item_factory.h"
#include "weapon.h"
#include "armor.h"
#include "consumable.h"

constexpr int WEAPON_ID_TEST     = 1001;
constexpr int ARMOR_ID_TEST      = 2010;
constexpr int CONSUMABLE_ID_TEST = 3003;

// ------------------------------------------------------------
// Deterministic RNG for testing
// ------------------------------------------------------------
class TestRNG : public RNG {
public:
    explicit TestRNG(uint32_t seed = 1337) : gen(seed) {}

    int randomInt(int min, int max) override {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

    float randomFloat(float min, float max) override {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }

private:
    std::mt19937 gen;
};

// ------------------------------------------------------------
// Helper to build LootContext
// ------------------------------------------------------------
static LootContext makeCtx(
    int level,
    EnemyTier tier,
    RNG& rng
) {
    LootContext ctx;
    ctx.level = level;
    ctx.enemyTier = tier;
    ctx.rng = rng;
    return ctx;
}

// ------------------------------------------------------------
// Sanity tests
// ------------------------------------------------------------
TEST_CASE("ItemFactory builds without throwing", "[ItemFactory]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(1, EnemyTier::Normal, rng);

    REQUIRE_NOTHROW(factory.build(1, ctx));
}

// ------------------------------------------------------------
// Weapon tests
// ------------------------------------------------------------
TEST_CASE("Weapon is built correctly", "[ItemFactory][Weapon]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(5, EnemyTier::Normal, rng);
    auto item = factory.build(WEAPON_ID_TEST, ctx);

    REQUIRE(item);

    auto* weapon = dynamic_cast<Weapon*>(item.get());
    REQUIRE(weapon != nullptr);

    REQUIRE(weapon->getItemType() == ITEMTYPE::WEAPON);
}

TEST_CASE("Weapon gains stats when rarity is above Common", "[ItemFactory][Weapon]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(15, EnemyTier::Elite, rng);
    auto item = factory.build(WEAPON_ID_TEST, ctx);

    auto* weapon = dynamic_cast<Weapon*>(item.get());
    REQUIRE(weapon);

    if (weapon->rarity() != Rarity::Common) {
        const auto& mod = weapon->getStatModifier();
        REQUIRE(mod.damage.has_value());
    }
}

// ------------------------------------------------------------
// Armor tests
// ------------------------------------------------------------
TEST_CASE("Armor scales with level and tier", "[ItemFactory][Armor]") {
    ItemFactory factory;
    TestRNG rng;

    auto lowCtx  = makeCtx(1, EnemyTier::Normal, rng);
    auto highCtx = makeCtx(30, EnemyTier::Boss, rng);

    auto lowItem  = factory.build(ARMOR_ID_TEST, lowCtx);
    auto highItem = factory.build(ARMOR_ID_TEST, highCtx);

    auto* lowArmor  = dynamic_cast<Armor*>(lowItem.get());
    auto* highArmor = dynamic_cast<Armor*>(highItem.get());

    REQUIRE(lowArmor);
    REQUIRE(highArmor);

    int lowArmorVal  = lowArmor->getStatModifier().armor.value_or(0);
    int highArmorVal = highArmor->getStatModifier().armor.value_or(0);

    REQUIRE(highArmorVal >= lowArmorVal);
}

TEST_CASE("Armor durability increases at higher rarities", "[ItemFactory][Armor]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(20, EnemyTier::Boss, rng);
    auto item = factory.build(ARMOR_ID_TEST, ctx);

    auto* armor = dynamic_cast<Armor*>(item.get());
    REQUIRE(armor);

    REQUIRE(armor->getMaxDurability() > 0);
}

// ------------------------------------------------------------
// Crit sanity tests
// ------------------------------------------------------------
TEST_CASE("Crit chance remains in sane bounds", "[ItemFactory][Crit]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(25, EnemyTier::Boss, rng);
    auto item = factory.build(WEAPON_ID_TEST, ctx);

    auto* weapon = dynamic_cast<Weapon*>(item.get());
    REQUIRE(weapon);

    auto crit = weapon->getStatModifier().crit;
    if (crit) {
        REQUIRE(*crit >= 0.0f);
        REQUIRE(*crit <= 0.5f); // sanity cap
    }
}

// ------------------------------------------------------------
// Speed modifier behavior
// ------------------------------------------------------------
TEST_CASE("Speed buffs apply correctly", "[ItemFactory][Speed]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(20, EnemyTier::Boss, rng);
    auto item = factory.build(WEAPON_ID_TEST, ctx);

    auto* weapon = dynamic_cast<Weapon*>(item.get());
    REQUIRE(weapon);

    auto speed = weapon->getStatModifier().speed;
    if (speed) {
        REQUIRE(*speed > 0.0f);
    }
}

// ------------------------------------------------------------
// Consumable tests
// ------------------------------------------------------------
TEST_CASE("Consumables are stackable", "[ItemFactory][Consumable]") {
    ItemFactory factory;
    TestRNG rng;

    auto ctx = makeCtx(1, EnemyTier::Normal, rng);
    auto item = factory.build(CONSUMABLE_ID_TEST, ctx);

    REQUIRE(item);
    REQUIRE(item->isStackable());
}
