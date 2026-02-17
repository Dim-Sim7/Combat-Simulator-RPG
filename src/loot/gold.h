#pragma once
//Gold → a specific configuration of LootableValue
#include "lootable_value.h"
class Gold final : public LootableValue {
public:
    Gold();

    Gold(int amount);

};