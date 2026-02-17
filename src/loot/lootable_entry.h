#pragma once

/**lootable_item represent an item that can be looted. A lootable item is initialised with an item and a
  weight is assigned based on the item type and rarity. Includes information such as is it unique and always drops

*/

#include "item.h"
#include <iostream>

struct LootEntry {
    int itemId;
    int weight;
    bool isUnique = false;
    bool isAlways = false;
};