#include "item_factory.h"
#include "item.h"


//responsible for creating item instances. Takes into account loot context to randomise loot
ItemFactory::ItemFactory()  {}


std::unique_ptr<Item> ItemFactory::build(int id, const LootContext& ctx) const {
    const ItemDef& base = db.itemDef(id);

    switch (base.type) {
        case ItemType::Weapon:
            return buildWeapon(base, db.weaponDef(id), ctx);

        case ItemType::Armor:
            return buildArmor(base, db.armorDef(id), ctx);

        case ItemType::Consumable:
            return buildConsumable(base, db.consumableDef(id), ctx);
        default:
            break;

    }

    throw std::logic_error("Unknown item type");

}

// struct LootContext {
//     int level; //level of loot source
//     MobType mobType; //humanoids drop more gold

//     EncounterType encounterType;   // Normal / Elite / Boss
//     LocationType locationType;     // Overworld / Dungeon

//     //OPTIONAL
//     std::optional<int> chestTier;
// // };
// struct StatModifier {
//     std::optional<std::pair<int, int>> damage;
//     std::optional<int> armor;
//     std::optional<float> speed;
//     std::optional<int> health;

    // void setDamageBuff(std::pair<int, int> inDamage);

    // void setSpeedBuff(float inSpeed);
    // void setArmorBuff(int inArmor);

    // void setHealthBuff(int inHealth);


//REMINDER - ALL ITEMS HAVE A STATMOD IN-BUILT. TO INCREASE STATS, USE THIS
//roll rarity here. Higher level mobs have higher chance of rarity
//bosses always drop high rarity
//elites have high chance of rarity
std::unique_ptr<Item> ItemFactory::buildWeapon(const ItemDef& base, const WeaponDef& weaponDef, const LootContext& ctx) const {
    //for weapons, increase damage based on level. adjust name with prefixes and suffixes
    //roll rari
    auto Weapon = std::make_unique<<Weapon>{base.name, weaponDef.weapon_id, weaponDef.minDamage, 
                                            weaponDef.maxDamage, weaponDef.speed, weaponDef.type};

    Rarity r = rollRarity(ctx);
    weapon->setRarity(r);

    upgradeWeapon(*weapon, ctx);

    return weapon;
}

std::unique_ptr<Item> ItemFactory::buildArmor(const ItemDef& base, const ArmorDef& armorDef, const LootContext& ctx) const {
    return Armor{base.name, armorDef.armor_id, armorDef.maxDurability, armorDef.armorType, armorDef.armorSlot};
}

std::unique_ptr<Item> ItemFactory::buildConsumable(const ItemDef& base, const ConsumableDef& consumableDef, const LootContext& ctx) const {
    return Consumable{base.name, consumableDef.consumable_id, consumableDef.stack_size, consumableDef.stackable,
                    consumableDef.duration, consumableDef.statMod, consumableDef.consumable_type};
}


//TODO decide if a rolled item is an upgrade or not based on mob level and mob rarity
//upgrade means -> higher rarity, higher stats, extra stats

//stats to consider --> damage min, dmg max, speed, health, armor, crit
void upgradeWeapon(Weapon& weapon, const LootContext& ctx) {
    weapon.setRarity(rollRarity(ctx));
    switch (weapon.rarity()) {
        case Rarity::Uncommon:
            weapon.setDamageBuff({1,3});
            weapon.s
    }

    
}

Rarity rollRarity(const LootContext& ctx) {
    RarityWeights w = BASE_WEIGHTS;
    w = applyTierModifier(w, ctx.enemyTier);
    w = applyLevelSaling(w, ctx.level);

    clampWeights(w);

    return rollFromWeights(w, ctx.rng);
}



RarityWeights applyTierModifier(RarityWeights w, EnemyTier tier) {
    switch (tier) {
        case EnemyTier::Elite:
            w.common -=15;
            w.uncommon += 5;
            w.rare += 7;
            w.epic += 3;
            break;

        case EnemyTier::Boss:
            w.common     -= 30;
            w.uncommon   += 10;
            w.rare       += 12;
            w.epic       += 6;
            w.legendary  += 2;
            break;
        
        default:
            break;
    }
    return w;
}

RarityWeights applyLevelScaling(RarityWeights w, int level) {
    int bonus = level / 5; // every 5 levels

    w.common     -= bonus * 2;
    w.uncommon   += bonus;
    w.rare       += bonus;
    w.epic       += bonus / 2;

    if (level >= 20)
        w.legendary += 1;

    return w;
}

void clampWeights(RarityWeights& w) {
    w.common     = std::max(0, w.common);
    w.uncommon   = std::max(0, w.uncommon);
    w.rare       = std::max(0, w.rare);
    w.epic       = std::max(0, w.epic);
    w.legendary  = std::max(0, w.legendary);
}

Rarity rollFromWeights(const RarityWeights& w, RNG& rng) {
    int total = w.common + w.uncommon + w.rare + w.epic + w.legendary;
    int roll = rng.randomInt(1, total);

    if ((roll -= w.common) <=0) return Rarity::Common;
    if ((roll -= w.uncommon) <= 0) return Rarity::Uncommon;
    if ((roll -= w.rare) <= 0) return Rarity::Rare;
    if ((roll -= w.epic) <= 0) return Rarity::Epic;
    return Rarity::Legendary;
}