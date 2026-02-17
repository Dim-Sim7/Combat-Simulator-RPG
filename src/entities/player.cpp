#include "player.h"
#include "../items/item.h"
#include "../items/weapon.h"

Player::Player() : Entity(), 
    EXP(100u, 0u) {}

Player::Player(const StatBlock& statsInit, 
    const int hpInitCurr, 
    const int hpInitMax, 
    const std::vector<Abilities>& abilitiesInit,
    const std::string& nameInit)
    : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit),
    EXP(100u, 0u) {}


void Player::gainExp(int earnedEXP)
{
    EXP.increaseCurrent(earnedEXP);

    std::cout << "You gain " << earnedEXP << " experience.\n";
    if (EXP.getCurrent() == EXP.getMax())
    {
        EXP.setCurrent(0);
        EXP.setMax(getEXPToLevel());
        levelUp();
    }
}


void Player::onDeath()
{
    std::cout << getEntityName() << " has died!" << '\n';
}

void Player::unequipToInventory(EQUIP_SLOT_TYPE slot)
{
    if (auto* item = equipSlots->getItemFromSlot(slot)) {
        inventory.addItem(item);
        equipSlots->unequipItem(slot);
    }
}


bool Player::equipItem(Item& itemToEquip) {

    if (itemToEquip.getItemType() == ITEMTYPE::WEAPON) {
        return equipWeapon(itemToEquip);
    }
    else if (itemToEquip.getItemType() == ITEMTYPE::ARMOR) {
        return equipArmor(itemToEquip);
    }
    return false;

}

bool Player::equipWeapon(Item& itemToEquip)
{
    auto* newWeapon = dynamic_cast<Weapon*>(&itemToEquip);
    if (!newWeapon)
        return false;

    EQUIP_SLOT_TYPE targetSlot = EQUIP_SLOT_TYPE::MAIN_HAND;

    // TWO-HANDED
    if (newWeapon->isTwoHanded())
    {
        unequipToInventory(EQUIP_SLOT_TYPE::MAIN_HAND);
        unequipToInventory(EQUIP_SLOT_TYPE::OFF_HAND);

        equipSlots->equipItem(itemToEquip, EQUIP_SLOT_TYPE::MAIN_HAND);
    }
    // ONE-HANDED
    else
    {
        if (auto* current = equipSlots->getItemFromSlot(EQUIP_SLOT_TYPE::MAIN_HAND))
        {
            if (auto* currentWeapon = dynamic_cast<Weapon*>(current);
                currentWeapon &&
                currentWeapon->getDamageBuff().first < newWeapon->getDamageBuff().first)
            {
                unequipToInventory(EQUIP_SLOT_TYPE::MAIN_HAND);
                targetSlot = EQUIP_SLOT_TYPE::MAIN_HAND;
            }
            else
            {
                unequipToInventory(EQUIP_SLOT_TYPE::OFF_HAND);
                targetSlot = EQUIP_SLOT_TYPE::OFF_HAND;
            }
        }

        equipSlots->equipItem(itemToEquip, targetSlot);
    }

    inventory->remove(&itemToEquip);
    recalculateStats();
    return true;
}


bool Player::equipArmor(Item& itemToEquip)
{
    auto* newArmor = dynamic_cast<Armor*>(&itemToEquip);
    if (!newArmor)
        return false;

    EQUIP_SLOT_TYPE slot =
        equipSlots->toEquipSlot(newArmor->armorSlot());

    unequipToInventory(slot);

    equipSlots->equipItem(itemToEquip, slot);
    inventory.remove(&itemToEquip);
    recalculateStats();

    return true;
}


//IMPLEMENT
void Player::recalculateStats()
{
    StatModifier newStatMod = equipSlots->getTotalStatMods();
    stats.applyStatModifier(newStatMod);

    int newMaxHP = HP.getMax() + newStatMod.health.value_or(0);
    HP.setMax(newMaxHP);
    HP.increaseCurrent(newStatMod.health.value_or(0));
}

void Player::levelUp()
{
    stats.levelUp();
    
    if (stats.getLevel() % 5 == 0) //Every 5 levels, gain an ability
    {
        Abilities newAbility = aPool->getRandomAbility(abilities);
        if (newAbility.getName() != "None") 
        {
            abilities.push_back(newAbility);
            std::cout << name << " learned a new ability: " << newAbility.getName() << "!\n";
        }
    }

    
}

int Player::getEXPToLevel()
{
    int curLvl = stats.getLevel();
    int EXPtoLevel = 0;
    if (curLvl < 11) // level 1 to 11
    {
        EXPtoLevel = (40 * (curLvl * curLvl)) +  (360 * curLvl);
    }
    else if (curLvl < 27) // level 11 to 27
    {
        EXPtoLevel = static_cast<int>((-0.4 * pow(curLvl, 3)) + (40.4 * pow(curLvl, 2)) + (396 * curLvl));
    }
    else if (curLvl <= 59) //level 27 to 59
    {
        EXPtoLevel = static_cast<int>(((65 * pow(curLvl, 2)) - (165 * curLvl) - 6750) * 0.82);
    }
    else //level 60+
    {
        EXPtoLevel = 155 + (235 + (5 * curLvl)) * (1344 - 69 - ((69 - curLvl) * (3 + (69 - curLvl) * 4)));
    }

    return EXPtoLevel;
    
    
}





