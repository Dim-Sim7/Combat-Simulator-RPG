#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "rng.cpp"
//This class represents a loot table for a container to generate based on the source context
//It includes methods to assign weights 

struct LootRow {
    int itemId;
    int minLevel;
    int maxLevel;
    int baseWeight;
    bool isBoss;
};

class Table {

public:
    Table(const LootContext& ctx) {
        read_master_table(lootIdTable&, ctx);
        //rollitems
        //upgrade items based on ctx
        //return items
    }

    void hitItems(Container& container, const LootContext& ctx) {
        int sum = sumWeights();
        setItemsToHit();

        //roll the number of items to hit
        int numberOfItems = randomInt(itemsToHit.first, itemsToHit.second);

        for (size_t i = 0; i < numberOfItems; i++) {
            int roll = randomInt(0, sum - 1);
            int itemId = hitItem(roll);

            baseItems.push_back(getRolledItem(itemId));
        }

    }
    
private:
    std::vector<LootRow> lootIdTable;
    std::vector<std::weak_ptr<Lootable>> baseItems;

    std::pair<int, int> itemsToHit;

    void read_master_table(const LootContext& ctx) {
        //read master table
        //fill loot table with id's of base items with ctx parameters
        //e.g. level 3 mob, beast type, dungeon
        std::ifstream file("master_loot_table.csv");
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return 1;
        }

        std::string line;
        // Skip header
        std::getline(file, line);
        

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;

            LootRow row;

            std::getline(ss, token, ',');
            row.itemId = std::stoi(token);

            std::getline(ss, token, ',');
            row.minLevel = std::stoi(token);

            std::getline(ss, token, ',');
            row.maxLevel = std::stoi(token);

            if (ctx.level < row.minLevel || ctx.level > row.maxLevel) {
                continue; //row is destroyed at next iteration
            }

            std::getline(ss, token, ',');
            row.baseWeight = std::stoi(token);

            std::getline(ss, token, ',');
            row.isBoss = parseBool(token);

            lootIdTable.push_back(row);

        }

    }

    int hitItem(int roll) {
        int running = 0;

        for (auto& entry : lootIdTable()) {
            running += entry.baseWeight;
            if (roll < running) {
                return entry.itemId;
            }
        }
    }

    int sumWeights() {
        int sum{0};
        for (auto& c : lootIdTable) {
            sum += c.baseWeight;
        }
        
        return sum;
    }

    void setItemsToHit(const LootContext% ctx) {
        int maxItems = 2;
        int minItems = 0;

        if (ctx.isDungeon && ctx.isElite) {
            maxItems = 3;
        }

        if (ctx.isBoss) {
            maxItems = 6;
            minItems = 3;
        }

        if (chestTier > 1) {
            maxItems = 5;
            minItems = 2;
        }

        itemsToHit = std::make_pair(minItems, maxItems);
    }

    LootableItem& getHitItem(int itemId) {

    }


};