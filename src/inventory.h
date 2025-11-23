#pragma once

#include "item.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>

class Inventory
{

public:

    Inventory(): gold(0u) {}

    void addItem(Item& itemToAdd)
    {
        if (Item* existing = findItem(itemToAdd))
        {
            if (existing->isStackable())
            {
                item->incrementStackSize(); //increment item in inventory
                return;
            }
            
        }

        items.push_back(&itemToAdd);

    }

    void removeItem(Item& item)
    {
        Item* stored = findItem(item);

        if (!stored)
        {
            std::cout << item.getName() << " doesn't exist in your inventory!\n";
            return;
        }

        stored->decrementStackSize();

        if (stored->noMoreStackSize())
            items.erase(std::remove(items.begin(), items.end(), stored), items.end());
    }

    void printInventory() const
    {
        std::cout << "-------- INVENTORY --------\n";
        for (const auto& item: items)
        {
            std::cout << item->getName() << "\n";
        }
        std::cout << "----------------\n";
    }

    //implement get all consumables, weapons, armor
    std::vector<Item*> getItemsByType(ITEMTYPE type) const
    {
        std::vector<Item*> specificItems;
        for (auto* item : items)
        {
            if (item->getType() == type)
                result.push_back(item);
        }
        return specificItems;
    }

    Item* findItem(const Item& itemToCheck)
    {
        for (auto* item : items)
            if (item->getID() == itemToCheck.getID())
                return item;
        return nullptr;
    }

    void addGold(int inGold)
    {
        if (inGold > 0)
            gold += inGold;
    }

private:
    std::vector<Item*> items;
    int gold;

    bool alreadyExists(const Item& itemToCheck) 
    {
        bool found = false;

        for (auto* item: items)
        {
            if (item->getID() == itemToCheck.getID())
            {
                found = true;
                break;
            }

        }
        return found;
    }


};
