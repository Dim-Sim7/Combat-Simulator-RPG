#include "battlesystem.h"

#include <iostream>


BattleSystem::BattleSystem()
    : running(false)
{
    startTime = std::chrono::steady_clock::now();
}

BattleSystem::~BattleSystem()
{
    running = false;
    if (inputThread.joinable())
        inputThread.join();
}

void BattleSystem::battleLoop(Player& player, NPC& enemy)
{
    running = true;

    inputThread = std::thread([&]() {
        inputLoop(player);
    });

    enemyAI = std::make_unique<NPC_AI>(&enemy, &player);

    while (running)
    {
        float now = getTime();
        player.update(now);
        enemy.update(now);

        if (!enemy.isCasting() && enemyAI)
            enemyAI->update(now);

        if (enemy.hasFledCombat()) {
            std::cout << enemy.getEntityName() << " fled from combat!\n";
            break;
        }

        Command cmd;
        while (popCommand(cmd)) {
            if (!player.cast.isCasting)
                handleCommand(player, enemy, cmd, now);
        }

        if (enemy.isDead()) {
            player.gainExp(enemy.expOnDeath());
            enemy.onDeath();
            break;
        }

        if (player.isDead()) {
            player.onDeath();
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    running = false;
    if (inputThread.joinable())
        inputThread.join();

    enemyAI.reset();
}

float BattleSystem::getTime()
{
    return std::chrono::duration<float>(
        std::chrono::steady_clock::now() - startTime
    ).count();
}


void BattleSystem::pushCommand(PlayerCommand command, float currentTime, const std::string& data)
{
    std::lock_guard<std::mutex> lock(commandMutex);
    commandQueue.push({command, data, currentTime});
}

bool BattleSystem::popCommand(Command& out)
{
    std::lock_guard<std::mutex> lock(commandMutex);
    if (commandQueue.empty()) return false;
    out = commandQueue.front();
    commandQueue.pop();
    return true;
}

void BattleSystem::inputLoop(Player& player)
{
    while (running)
    {
        if (!std::cin.good()) {
            std::cin.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        std::cout << "\n" << player.getEntityName()
                  << " HP: " << player.getCurrentHP()
                  << "/" << player.getMaxHP() << "\n";

        std::cout << "\n===== ACTIONS =====\n";
        std::cout << "[1] Melee Attack\n";

        const auto& spells = player.getAbilities();
        const auto& items =
            player.getInventory()->getItemsByType(ITEMTYPE::CONSUMABLE);

        int optionIndex = 2;

        for (const auto& sp : spells)
            std::cout << "[" << optionIndex++ << "] Spell: " << sp.getName() << "\n";

        for (const auto& it : items)
            std::cout << "[" << optionIndex++ << "] Item: " << it->getName() << "\n";

        std::cout << "> ";
        int choice;
        if (!(std::cin >> choice)) {
            running = false;
            break;
        }

        float now = getTime();

        if (choice == 1) {
            pushCommand(PlayerCommand::Attack, now);
            continue;
        }

        int spellStart = 2;
        int spellEnd = spellStart + spells.size() - 1;

        if (choice >= spellStart && choice <= spellEnd) {
            pushCommand(PlayerCommand::Spell, now, spells[choice - spellStart].getName());
            continue;
        }

        int itemStart = spellEnd + 1;
        int itemEnd = itemStart + items.size() - 1;

        if (choice >= itemStart && choice <= itemEnd) {
            pushCommand(PlayerCommand::Consumable, now, items[choice - itemStart]->getName());
            continue;
        }

        std::cout << "[INVALID INPUT]\n";
    }
}

void BattleSystem::handleCommand(Player& player, NPC& enemy, const Command& cmd, float now)
{
    switch (cmd.type)
    {
        case PlayerCommand::Attack:
            player.attack(enemy, now);
            break;

        case PlayerCommand::Spell:
            player.tryCastSpell(cmd.data, &enemy, now);
            break;

        case PlayerCommand::Consumable:
            player.tryUseConsumable(cmd.data, now);
            break;

        default:
            break;
    }
}


// ============================================================
// COMBAT EXECUTION
// ============================================================






