#pragma once

#include "item.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>

class Inventory:
{

public:

    Inventory(): gold(0u) {}

    void addItem(Item& item)
    {
        if(alreadyExists(item))
        {
            item.incrementStackSize();
        }
        else
        {
            items.push_back(item);
        }

    }

    void removeItem(Item& item)
    {
        if(alreadyExists(item))
        {
            item.decrementStackSize();
        }
        else
        {
            std::cout << item.getName() << " doesn't exist in your inventory! " << "\n";
        }
        if(item.noMoreStackSize())
        {
            items.pop_back(item);
        }
    }

    //implement get all consumables, weapons, armor, jewelery



    


private:
    std::vector<Item> items;
    uint32_t gold;

    bool alreadyExists(const Item& item) 
    {
        bool exists = false;
        if(std::find(items.begin(), items.end(), item) != items.end())
        {
            exists = true;
        }

        return exists;
    }


};
