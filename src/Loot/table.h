#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "rng.h"
#include "loot_context.h"

struct LootRow {
    int itemId;
    int minLevel;
    int maxLevel;
    int baseWeight;
    bool bossOnly;
};

class LootTable {
public:
    explicit LootTable(const LootContext& ctx) {
        readMasterTable(ctx);
        setItemsToHit(ctx);
    }

    std::vector<int> rollItemIds() const {
        std::vector<int> result;

        int count = randomInt(itemsToHit_.first, itemsToHit_.second);
        int totalWeight = sumWeights();

        for (int i = 0; i < count; ++i) {
            int roll = randomInt(0, totalWeight - 1);
            result.push_back(hitItem(roll));
        }

        return result;
    }

private:
    std::vector<LootRow> lootRows_;
    std::pair<int, int> itemsToHit_{0, 0};

    void readMasterTable(const LootContext& ctx) {
        std::ifstream file("master_loot_table.csv");
        if (!file.is_open()) {
            std::cerr << "Error opening loot table\n";
            return;
        }

        std::string line;
        std::getline(file, line); // header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            LootRow row;
            std::string token;

            std::getline(ss, token, ',');
            row.itemId = std::stoi(token);

            std::getline(ss, token, ',');
            row.minLevel = std::stoi(token);

            std::getline(ss, token, ',');
            row.maxLevel = std::stoi(token);

            if (ctx.level < row.minLevel || ctx.level > row.maxLevel)
                continue;

            std::getline(ss, token, ',');
            row.baseWeight = std::stoi(token);

            std::getline(ss, token, ',');
            row.bossOnly = parseBool(token);

            if (row.bossOnly && ctx.encounterType != EncounterType::Boss)
                continue;

            lootRows_.push_back(row);
        }
    }

    int hitItem(int roll) const {
        int running = 0;
        for (const auto& row : lootRows_) {
            running += row.baseWeight;
            if (roll < running)
                return row.itemId;
        }
        return lootRows_.back().itemId;
    }

    int sumWeights() const {
        int sum = 0;
        for (const auto& row : lootRows_)
            sum += row.baseWeight;
        return sum;
    }

    void setItemsToHit(const LootContext& ctx) {
        int minItems = 0;
        int maxItems = 2;

        if (ctx.locationType == LocationType::Dungeon)
            maxItems++;

        if (ctx.encounterType == EncounterType::Elite)
            maxItems++;

        if (ctx.encounterType == EncounterType::Boss) {
            minItems = 3;
            maxItems = 6;
        }

        if (ctx.chestTier && *ctx.chestTier > 1) {
            minItems++;
            maxItems += 2;
        }

        itemsToHit_ = {minItems, maxItems};
    }
};
