#pragma once
#include <cstdint>
#include <random>
#include <iostream>
#include <memory>

enum class ITEMTYPE { WEAPON, ARMOR, CONSUMABLE, MISC }

class Item:
{
public:


    Item() : name(""), id(0), stackSize(0), stackable(false) {}

    Item(std::string inName, int inId, int inStackSize, bool inStackable)
    : name(inName), id(inId), stackSize(inStackSize), stackable(inStackable) {}



    std::string getName() { return name; }
    int getID() { return id; }
    int getStackSize() { return stackSize; }
    bool getStackable() { return stackable; }

    void setName(std::string inName) { name = inName; }
    void setID(int inID) { id = inID; }
    void setStackSize(int inStackSize) { stackSize = inStackSize; }
    void setStackable(bool inStackable) { stackable = inStackable; }

    void incrementStackSize() { ++stackSize; }
    void decrementStackSize() { --stackSize; }

    bool noMoreStackSize() { return stackSize == 0; }

    virtual void use() = 0;
    virtual ~Item() = default;

private:
    std::string name;
    int id;
    int stackSize;
    bool stackable;
};
