#include "lootable_value.h"


LootableValue::LootableValue()
    : amount_(0),
      weight_(0),
      isUnique_(false),
      isAlways_(false)
{
}

LootableValue::LootableValue(int amount, int weight, bool unique, bool always)
    : amount_(amount),
      weight_(weight),
      isUnique_(unique),
      isAlways_(always)
{
}
int LootableValue::amount() const { return amount_; }
int LootableValue::setAmount(int amount)
{
    amount_ = amount;
    return amount_;
}

int LootableValue::weight() const override { return weight_; }
void LootableValue::setWeight(int weight)
{
    weight_ = weight;
}

bool LootableValue::isUnique() const override { return isUnique_; }
void LootableValue::setUnique(bool unique)
{
    isUnique_ = unique;
}

bool LootableValue::isAlways() const override { return isAlways_; }
void LootableValue::setAlways(bool always)
{
    isAlways_ = always;
}
