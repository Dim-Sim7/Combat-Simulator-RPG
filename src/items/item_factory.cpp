#include "item_factory.h"

//responsible for creating item instances. Takes into account loot context to randomise loot
ItemFactory::ItemFactory() : db()  {}


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


std::unique_ptr<Item> ItemFactory::buildWeapon(const ItemDef& base, const WeaponDef& weaponDef, const LootContext& ctx) const {
    //for weapons, increase damage based on level. adjust name with prefixes and suffixes
    //roll rari
    auto weapon = std::make_unique<Weapon>{base.name, weaponDef.weapon_id, weaponDef.minDamage, 
                                            weaponDef.maxDamage, weaponDef.speed, weaponDef.type};

    Rarity r = rollRarity(ctx);
    weapon->setRarity(r);
    upgradeWeapon(*weapon, ctx);
    return weapon;
}

std::unique_ptr<Item> ItemFactory::buildArmor(const ItemDef& base, const ArmorDef& armorDef, const LootContext& ctx) const {
    auto armor = std::make_unique<Armor>{base.name, armorDef.armor_id, armorDef.maxDurability, armorDef.armorType, armorDef.armorSlot};

    Rarity r = rollRartity(ctx);
    armor->setRarity(r);
    upgradeArmor(*armor, ctx);
    return armor;
}

std::unique_ptr<Item> ItemFactory::buildConsumable(const ItemDef& base, const ConsumableDef& consumableDef, const LootContext& ctx) const {
    return std::make_unique<Consumable>{base.name, consumableDef.consumable_id, consumableDef.stack_size, consumableDef.stackable,
                    consumableDef.duration, consumableDef.statMod, consumableDef.consumable_type};
}


RarityWeights ItemFactory::applyTierModifier(RarityWeights w, EnemyTier tier) {
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

RarityWeights ItemFactory::applyLevelScaling(RarityWeights w, int level) {
    int bonus = level / 5; // every 5 levels

    w.common     -= bonus * 2;
    w.uncommon   += bonus;
    w.rare       += bonus;
    w.epic       += bonus / 2;

    if (level >= 20)
        w.legendary += 1;

    return w;
}

void ItemFactory::clampWeights(RarityWeights& w) {
    w.common     = std::max(0, w.common);
    w.uncommon   = std::max(0, w.uncommon);
    w.rare       = std::max(0, w.rare);
    w.epic       = std::max(0, w.epic);
    w.legendary  = std::max(0, w.legendary);
}

Rarity ItemFactory::rollFromWeights(const RarityWeights& w, RNG& rng) {
    int total = w.common + w.uncommon + w.rare + w.epic + w.legendary;
    int roll = rng.randomInt(1, total);

    if ((roll -= w.common) <=0) return Rarity::Common;
    if ((roll -= w.uncommon) <= 0) return Rarity::Uncommon;
    if ((roll -= w.rare) <= 0) return Rarity::Rare;
    if ((roll -= w.epic) <= 0) return Rarity::Epic;
    return Rarity::Legendary;
}

Rarity ItemFactory::rollRarity(const LootContext& ctx) {
    RarityWeights w = BASE_WEIGHTS;
    w = applyTierModifier(w, ctx.enemyTier);
    w = applyLevelSaling(w, ctx.level);
    clampWeights(w);

    return rollFromWeights(w, ctx.rng);
}

void ItemFactory::upgradeArmor(Armor& armor, const LootContext& ctx) {
    armor.setRarity(rollRarity(ctx));

    float scale = levelScale(ctx.level) * tierScale(ctx.enemyTier);

    auto scaleInt = [&](int base) {
        return static_cast<int>(base * scale);
    };

    switch (armor.rarity()) {
        case Rarity::Common:
            break;

        case Rarity::Uncommon:
            armor.setArmorBuff(scaleInt(ctx.rng.randomInt(5, 15)));
            armor.setHealthBuff(scaleInt(ctx.rng.randomInt(1, 5)));
            break;

        case Rarity::Rare:
            armor.setArmorBuff(scaleInt(ctx.rng.randomInt(10, 30)));
            armor.setHealthBuff(scaleInt(ctx.rng.randomInt(5, 15)));
            armor.setCritBuff(ctx.rng.randomInt(1, 2) * 0.01f); // 1–2%
            break;

        case Rarity::Epic:
            armor.setArmorBuff(scaleInt(ctx.rng.randomInt(25, 50)));
            armor.setHealthBuff(scaleInt(ctx.rng.randomInt(15, 45)));
            armor.setCritBuff(ctx.rng.randomInt(1, 3) * 0.01f);
            armor.setMaxDurability(
                armor.getMaxDurability() + scaleInt(ctx.rng.randomInt(25, 50))
            );
            break;

        case Rarity::Legendary:
            armor.setArmorBuff(scaleInt(ctx.rng.randomInt(50, 100)));
            armor.setHealthBuff(scaleInt(ctx.rng.randomInt(25, 60)));
            armor.setCritBuff(ctx.rng.randomInt(2, 4) * 0.01f);
            armor.setMaxDurability(
                armor.getMaxDurability() + scaleInt(ctx.rng.randomInt(50, 80))
            );
            break;
    }
}


void ItemFactory::upgradeWeapon(Weapon& weapon, const LootContext& ctx) {
    weapon.setRarity(rollRarity(ctx));
    float scale = levelScale(ctx.level) * tierScale(ctx.enemyTier);

    auto scaleRange = [&](std::pair<int,int> base) {
        return std::make_pair(
            static_cast<int>(base.first  * scale),
            static_cast<int>(base.second * scale)
        );
    };

    switch (weapon.rarity()) {
        case Rarity::Common:
            // no bonus
            break;

        case Rarity::Uncommon:
            weapon.setDamageBuff(scaleRange({1, 3}));
            break;

        case Rarity::Rare:
            weapon.setDamageBuff(scaleRange({2, 5}));
            weapon.setCritBuff(ctx.rng.randomInt(1,4));
            weapon.setHealthBuff(ctx.rng.randomInt(1,20));
            break;

        case Rarity::Epic:
            weapon.setDamageBuff(scaleRange({4, 8}));
            weapon.setCritBuff(ctx.rng.randomInt(2,7));
            weapon.setSpeedBuff(ctx.rng.randomFloat(0.05f, 0.15f));
            weapon.setHealthBuff(ctx.rng.randomInt(10,40));
            break;

        case Rarity::Legendary:
            weapon.setDamageBuff(scaleRange({8, 15}));
            weapon.setCritBuff(ctx.rng.randomInt(4,10));
            weapon.setSpeedBuff(ctx.rng.randomFloat(0.10f, 0.30f));
            weapon.setHealthBuff(ctx.rng.randomInt(20,80));
            break;
    }
}

    
