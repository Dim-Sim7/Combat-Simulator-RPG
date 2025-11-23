#include "item.h"


Item::Item() : name(""), id(0), type(ITEMTYPE::MISC), stackSize(0), stackable(false) {}

Item::Item(std::string& inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable)
: name(inName), id(inId), type(inType), stackSize(inStackSize), stackable(inStackable) {}

virtual ~Item() = default;


const std::string Item::getName() { return name; }
const int Item::getID() { return id; }
const int Item::getStackSize() { return stackSize; }
const bool Item::isStackable() { return stackable; }
const ITEMTYPE Item::getItemType() { return type; }

void Item::setName(std::string inName) { name = inName; }
void Item::setID(int inID) { id = inID; }
void Item::setType(ITEMTYPE inType) { type = inType; }
void Item::setStackSize(int inStackSize) { stackSize = inStackSize; }
void Item::setStackable(bool inStackable) { stackable = inStackable; }

void Item::incrementStackSize() { ++stackSize; }
void Item::decrementStackSize() { --stackSize; }

bool Item::noMoreStackSize() { return stackSize == 0; }

const StatModifier& Item::getStatModifier() const {
    return statMod;
}

void Item::setDamageBuff(std::pair<int, int> inDamage)
{
    statMod.damage = inDamage;
}

void Item::setSpeedBuff(float inSpeed)
{
    statMod.speed = inSpeed;
}

void Item::setArmorBuff(int inArmor)
{
    statMod.armor = inArmor;
}

void Item::setHealthBuff(point_t inHealth)
{
    statMod.health = inHealth;
}

[[nodiscard]] std::pair<int, int> Item::getDamageBuff() const
{
    return statMod.damage;
}

[[nodiscard]] float Item::getSpeedBuff() const
{
    return statMod.speed;
}

[[nodiscard]] int Item::getArmorBuff() const
{
    return statMod.armor;
}

[[nodiscard]] point_t Item::getHealthBuff() const
{
    return statMod.health;
}
