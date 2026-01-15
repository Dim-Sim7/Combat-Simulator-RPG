#pragma once


class LootableValue : public Lootable {

public:
    LootableValue();
    LootableValue(int amount, int weight, bool unique, bool always);

    int amount() const { return amount_; }
    int setAmount(int amount);

    int weight() const override { return weight_; }
    void setWeight(int weight);

    bool isUnique() const override { return isUnique_; }
    void setUnique(bool unique);

    bool isAlways() const override { return isAlways_; }
    void setAlways(bool always);


private:
    int amount_;
    int weight_;

    bool isUnique_;
    bool isAlways_;



}