#pragma once


class LootableValue : public Lootable {

public:
    LootableValue();
    LootableValue(int amount, int weight, bool unique, bool always);

    int amount() const;
    int setAmount(int amount);

    int weight() const override;
    void setWeight(int weight);

    bool isUnique() const override;
    void setUnique(bool unique);

    bool isAlways() const override;
    void setAlways(bool always);


private:
    int amount_;
    int weight_;

    bool isUnique_;
    bool isAlways_;



};