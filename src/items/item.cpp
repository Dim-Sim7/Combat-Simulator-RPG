#include "item.h"


Item::Item() : name(""), id(0), type(ITEMTYPE::MISC), stackSize(0), stackable(false) {}

Item::Item(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable)
: name(inName), id(inId), type(inType), stackSize(inStackSize), stackable(inStackable) {}

Item::~Item() = default;


const std::string& Item::getName() const { return name; }
int Item::getID() const { return id; }
int Item::getStackSize() const { return stackSize; }
bool Item::isStackable() const { return stackable; }
ITEMTYPE Item::getItemType() const { return type; }

void Item::setName(const std::string& inName) { name = inName; }
void Item::setID(int inID) { id = inID; }
void Item::setType(ITEMTYPE inType) { type = inType; }
void Item::setStackSize(int inStackSize) { stackSize = inStackSize; }
void Item::setStackable(bool inStackable) { stackable = inStackable; }

void Item::incrementStackSize() { ++stackSize; }
void Item::decrementStackSize() { 
    --stackSize; 
    if (stackSize < 0) 
        stackSize = 0; 
    }

bool Item::noMoreStackSize() const { return stackSize == 0; }

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

void Item::setHealthBuff(int inHealth)
{
    statMod.health = inHealth;
}

[[nodiscard]] std::pair<int,int> Item::getDamageBuff() const {
    return statMod.damage.value_or(std::pair<int,int>{0, 0});
}

[[nodiscard]] std::optional<float> Item::getSpeedBuff() const
{
    return statMod.speed;
}

[[nodiscard]] std::optional<int> Item::getArmorBuff() const
{
    return statMod.armor;
}

[[nodiscard]] std::optional<int> Item::getHealthBuff() const
{
    return statMod.health;
}

void Item::setRarity(const Rarity& rarity) {
    rarity_ = rarity;
}

Rarity Item::rarity() const {
    return rarity_;
}



