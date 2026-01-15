#include <iostream>
#include "statblock.h"
#include "pointwell.h"
#include "player.h"
#include "battlesystem.h"
#include "npc.h"
#include "abilities.h"
#include "item.h"
#include <cstdint>
#include <memory>
#include "RandomDistributionSystem/RDSTable.h"
#include "RandomDistributionSystem/RDSTable.h"

int main()
{
    // RDSTable must be owned by shared_ptr (shared_from_this is used)
    auto table = std::make_shared<RDSTable>();

    // Add 6 items with equal probability
    table->AddEntry(std::make_shared<LootItem>("Item 1", 1), 10, false, false, true);
    table->AddEntry(std::make_shared<LootItem>("Item 2", 2), 10, false, false, true);
    table->AddEntry(std::make_shared<LootItem>("Item 3", 3), 10, false, false, true);
    table->AddEntry(std::make_shared<LootItem>("Item 4", 4), 10, false, false, true);
    table->AddEntry(std::make_shared<LootItem>("Item 5", 5), 10, false, false, true);

    // Keep reference to item 6
    auto item6 = std::make_shared<LootItem>("Item 6", 6);
    table->AddEntry(item6, 10, false, false, true);

    // Want 2 drops
    table->setRDSCount(2);

    std::cout << "Step 1: Just loot 2 out of 6 - 3 runs\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Run " << (i + 1) << "\n";
        auto result = table->rdsResult();
        for (const auto& item : result) {
            std::cout << "    " << item->toString(0) << "\n";
        }
    }

    // Set Item 6 to always drop
    item6->setAlways(true);

    std::cout << "\nStep 2: Item 6 is now Always=true - 3 runs\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Run " << (i + 1) << "\n";
        auto result = table->rdsResult();
        for (const auto& item : result) {
            std::cout << "    " << item->toString(0) << "\n";
        }
    }
}