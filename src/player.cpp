#include "player.h"

Player::~Player() = default;
Player::Player() : Entity(), 
    inventory(std::make_unique<Inventory>()), 
    equipSlots(std::make_unique<EquipSlots>()), 
    aPool(std::make_unique<AbilitiesPool>()), 
    EXP(100u, 0u) {}

Player::Player(const StatBlock& statsInit, 
    const int& hpInitCurr, 
    const int& hpInitMax, 
    const std::vector<Abilities>& abilitiesInit,
    const std::string& nameInit)
    : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit),
    inventory(std::make_unique<Inventory>()),
    equipSlots(std::make_unique<EquipSlots>()),
    aPool(std::make_unique<AbilitiesPool>()),
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





// //Handle item equip logic
// void Player::equipWeapon(Item& itemToEquip)
// {
//     //is item a weapon?
//     Weapon* newWeapon = dynamic_cast<Weapon*>(&itemToEquip);
//     if (!newWeapon)
//         return;

//     //2H LOGIC
//     if (newWeapon->isTwoHanded())
//     {
//         //Unequip main hand if occupied
//         if (auto* current = equipSlots.getItemFromSlot(EQUIP_SLOT_TYPE::MAIN_HAND))
//             inventory.addItem(current);
        
//         //Unequip offhand is necessary
//         if (equipSlots.isSlotEquipped(EQUIP_SLOT_TYPE::OFF_HAND))
//             inventory.addItem(equipSlots.getItemFromSlot(EQUIP_SLOT_TYPE::OFF_HAND));
        
//         equipSlots.equipItem(itemToEquip, EQUIP_SLOT_TYPE::MAIN_HAND);
//         return;
//     }

//     //1H LOGIC
//     if (auto* current = equipSlots.getItemFromSlot(EQUIP_SLOT_TYPE::MAIN_HAND))
//     {
//         Weapon* currentWeapon = dynamic_cast<Weapon*>(current);

//         //compare damage
//         if (currentWeapon && current->getDamageBuff().first < newWeapon->getDamageBuff().first)
//         {
//             //replace main hand
//             inventory.addItem(current);
//             equipSlots.equipItem(itemToEquip, EQUIP_SLOT_TYPE::MAIN_HAND);
//         }
//         else
//         {
//             //Equip off-hand
//             if (auto* offhand = equipSlots.getItemFromSlot(EQUIP_SLOT_TYPE::OFF_HAND))
//                 inventory.addItem(offhand);
            
//             equipSlots.equipItem(itemToEquip, EQUIP_SLOT_TYPE::OFF_HAND);
//         }
//     }
//     else
//     {
//         //No main-hand, equip directly
//         equipSlots.equipItem(itemToEquip, EQUIP_SLOT_TYPE::MAIN_HAND);
//     }
//     recalculateStats();
// }

//IMPLEMENT
void Player::recalculateStats()
{
    StatModifier newStatMod = equipSlots->getTotalStatMods();
    stats.applyStatModifier(newStatMod);
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



