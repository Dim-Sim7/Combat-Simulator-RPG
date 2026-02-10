#include "item.h"


Item::Item() : name_(""), id(0), type_(ITEMTYPE::MISC), stackSize_(0), stackable_(false), statMod_{}, rarity_(Rarity::Common) {}

Item::Item(std::string inName, int inId, ITEMTYPE inType, int inStackSize, bool inStackable)
: name_(inName), id_(inId), type_(inType), stackSize_(inStackSize), stackable_(inStackable), statMod_{}, rarity_(Rarity::Common) {}

Item::~Item() = default;

const StatModifier& Item::getStatModifier() const { return statMod_; }
const std::string& Item::getName() const { return name_; }
int Item::getID() const { return id_; }
int Item::getStackSize() const { return stackSize_; }
bool Item::isStackable() const { return stackable_; }
ITEMTYPE Item::getItemType() const { return type_; }

void Item::setName(const std::string& inName) { name_ = inName; }
void Item::setID(int inID) { id_ = inID; }
void Item::setType(ITEMTYPE inType) { type_ = inType; }
void Item::setStackSize(int inStackSize) { stackSize_ = inStackSize; }
void Item::setStackable(bool inStackable) { stackable_ = inStackable; }

void Item::incrementStackSize() { ++stackSize_; }
void Item::decrementStackSize() { 
    --stackSize_; 
    if (stackSize_ < 0) 
        stackSize_ = 0; 
    }

bool Item::noMoreStackSize() const { return stackSize_ == 0; }


void Item::setDamageBuff(std::pair<int, int> inDamage)
{
    statMod_.addDamage(inDamage);
}

void Item::setSpeedBuff(float inSpeed)
{
    statMod_.addSpeed(inSpeed);
}

void Item::setArmorBuff(int inArmor)
{
    statMod_.addArmor(inArmor);
}

void Item::setHealthBuff(int inHealth)
{
    statMod_.addHealth(inHealth);
}

void Item::setCritBuff(float inCrit)
{
    statMod_.addCrit(inCrit);
}

[[nodiscard]] std::pair<int,int> Item::getDamageBuff() const {
    return statMod_.damage.value_or(std::pair<int,int>{0, 0});
}

[[nodiscard]] std::optional<float> Item::getSpeedBuff() const
{
    return statMod_.speed;
}

[[nodiscard]] std::optional<int> Item::getArmorBuff() const
{
    return statMod_.armor;
}

[[nodiscard]] std::optional<int> Item::getHealthBuff() const
{
    return statMod_.health;
}

[[nodiscard]] std::optional<float> Item::getCritBuff() const
{
    return statMod_.crit;
}

void Item::setRarity(const Rarity& rarity) {
    rarity_ = rarity;
}

Rarity Item::rarity() const {
    return rarity_;
}



