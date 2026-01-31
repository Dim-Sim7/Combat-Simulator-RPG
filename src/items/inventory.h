#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include <algorithm>
class Item;
enum class ITEMTYPE;
class Inventory
{

public:

    Inventory();

    void addItem(Item* itemToAdd);

    void removeItem(Item* item);
    void printInventory() const;

    //implement get all consumables, weapons, armor
    std::vector<Item*> getItemsByType(ITEMTYPE type) const;

    Item* findItem(const Item* itemToCheck);

    void addGold(int inGold);

private:
    std::vector<Item*> items;
    int gold;

    bool alreadyExists(const Item& itemToCheck);


};
