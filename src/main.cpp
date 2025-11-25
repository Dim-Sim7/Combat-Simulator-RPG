#include <iostream>
#include "statblock.h"
#include "pointwell.h"
#include "player.h"
#include "battlesystem.h"
#include "npc.h"
#include "abilities.h"
#include "item.h"
#include <cstdint>
#include <memory>

int main() {
    // Create player
    Player player;
    player.setEntityName("Hero");
    player.getStats().setBaseDamage({2, 5});
    player.getStats().setBaseArmor(2);
    player.setHP(PointWell(100, 100));

    // Add a spell
    Abilities fireball("Fireball", {5, 10}, 5, 0, 0.0f, ability_t::INSTANT);
    player.getAbilities().push_back(fireball);

    // Add a consumable
    Item* potion = new Item("Potion", 1, ITEMTYPE::CONSUMABLE, 1, false);
    potion->setHealthBuff(10);
    player.inventory->addItem(potion);

    // Create enemy
    NPC enemy;
    enemy.setEntityName("Goblin");
    enemy.getStats().setBaseDamage({1, 3});
    enemy.getStats().setBaseArmor(1);
    enemy.setHP(PointWell(50, 50));

    // Add a spell to enemy
    Abilities poison("Poison", {2, 4}, 5, 0, 0.0f, ability_t::INSTANT);
    enemy.getAbilities().push_back(poison);

    // Start battle
    BattleSystem battle;
    battle.battleLoop(player, enemy);

    std::cout << "Battle ended.\n";
    return 0;
}
