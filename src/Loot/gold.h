#pragma once
//Gold → a specific configuration of LootableValue
class Gold final : public LootableValue {
public:
    Gold();

    Gold(int amount)
        : LootableValue(amount, 0, false, true) {}


};