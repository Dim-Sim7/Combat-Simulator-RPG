#include "inventory.h"
#include "item.h"
Inventory::Inventory(): gold(0u) {}

void Inventory::addItem(Item* itemToAdd)
{
    if (Item* existing = findItem(itemToAdd))
    {
        if (existing->isStackable())
        {
            existing->incrementStackSize(); //increment item in inventory
            return;
        }
        
    }

    items.push_back(itemToAdd);

}

void Inventory::removeItem(Item* item)
{
    Item* stored = findItem(const_cast<const Item*>(item));

    if (!stored)
    {
        std::cout << item->getName() << " doesn't exist in your inventory!\n";
        return;
    }

    stored->decrementStackSize();

    if (stored->noMoreStackSize())
        items.erase(std::remove(items.begin(), items.end(), stored), items.end());
}

void Inventory::printInventory() const
{
    std::cout << "-------- INVENTORY --------\n";
    for (const auto& item: items)
    {
        std::cout << item->getName() << "\n";
    }
    std::cout << "----------------\n";
}

//implement get all consumables, weapons, armor
std::vector<Item*> Inventory::getItemsByType(ITEMTYPE type) const
{
    std::vector<Item*> specificItems;
    for (auto* item : items)
    {
        if (item->getItemType() == type)
            specificItems.push_back(item);
    }
    return specificItems;
}

Item* Inventory::findItem(const Item* itemToCheck)
{
    for (auto* item : items)
        if (item->getID() == itemToCheck->getID())
            return item;
    return nullptr;
}

void Inventory::addGold(int inGold)
{
    if (inGold > 0)
        gold += inGold;
}



bool Inventory::alreadyExists(const Item& itemToCheck) 
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



