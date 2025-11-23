#pragma once

#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <iostream>
#include "npc_ai.h"
#include "player.h"

enum class PlayerCommand { Attack, Spell, Consumable, Run, None };
struct Command {
    PlayerCommand type = PlayerCommand::None;
    std::string data; //spell name or item name
    float timestamp;
}
class BattleSystem
{
public:
    BattleSystem() 
    {
        startTime = std::chrono::steady_clock::now();
        gcdEndTime = 0.f;
    }

    ~BattleSystem()
    {
        running = false;
        if (inputThread.joinable())
            inputThread.join();
    }


    //start a battle
    void battleLoop(Player& player, NPC& enemy)
    {

        running = true;

        //Start input thread
        inputThread = std::thread([&]() 
        { 
            inputLoop(player);     
        });

        enemyAI = std::make_unique<NPC_AI>(&enemy, &player);

        while (running)
        {
            float now = getTime();

            
            //Handle player spell casting
            if (player.cast.isCasting && now >= player.cast.castEnd)
            {
                handleSpellCast(&player, now);
            }

            //Handle enemy spell casting
            if (enemy.cast.isCasting && now >= enemy.cast.castEnd)
            {
                handleSpellCast(&enemy, now);
            }

            //Update enemyAI if not casting
            if (!enemy.cast.isCasting && enemyAI)
                enemyAI->update(now);

            if (enemy.hasFledCombat())
            {
                std::cout << enemy.getEntityName() << " fled from combat!\n";
                running = false;
                break;
            }

            Command cmd;
            while (popCommand(cmd))
            {
                // Player cannot issue new actions while casting
                if (!player.cast.isCasting)
                    handleCommand(player, enemy, cmd, now);
            }

            if (enemy.isDead())
            {
                player.gainExp(enemy.expOnDeath());
                enemy.onDeath();
                player.addLoot(enemy.dropLoot());
                running = false;
            }

            if (player.isDead())
            {
                player.onDeath();
                running = false;
            }
            // 16ms delay (~60 FPS loop)
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        // Clean up
        if (inputThread.joinable())
            inputThread.join();

        enemyAI.reset(); //destroy object the pointer was pointing to

    }



private:
    std::unique_ptr<NPC_AI> enemyAI;
    //TIME
    std::chrono::steady_clock::time_point startTime;

    float getTime()
    {
        return std::chrono::duration<float>(
            std::chrono::steady_clock::now() - startTime
        ).count();
    }

    // ============================================================
    // COMMAND QUEUE
    // ============================================================

    std::mutex commandMutex;
    std::queue<Command> commandQueue;

    void pushCommand(PlayerCommand command, float currentTime, const std::string& data = "")
    {
        std::lock_guard<std::mutex> lock(commandMutex); //mutex prevents multiple threads from accessing queue at the same time
        commandQueue.push({command, data, currentTime});
    }

    bool popCommand(Command& out)
    {
        std::lock_guard<std::mutex> lock(commandMutex);
        if (commandQueue.empty()) return false;
        out = commandQueue.front();
        commandQueue.pop();
        return true;
    }


    // ============================================================
    // INPUT THREAD
    // ============================================================
    std::atomic<bool> running = false;
    std::thread inputThread;

    void inputLoop(Player& player)
    {
        while (running)
        {
            if (!std::cin.good()) continue;

            std::cout << "\n===== ACTIONS =====\n";
            std::cout << "[1] Melee Attack\n";

            const auto& spells = player.getAbilities();
            const auto& items = player.inventory.getConsumables();

            int optionIndex = 2;
            // spells
            for (auto& sp : spells)
            {
                std::cout << "[" << optionIndex << "] Spell: " << sp.getName() << "\n";
                optionIndex++;
            }

            // consumables
            for (auto& it : items)
            {
                std::cout << "[" << optionIndex << "] Item: " << it.getName() << "\n";
                optionIndex++;
            }

            std::cout << "> ";
            int choice;
            std::cin >> choice;

            float now = getTime();

            //Attack
            if (choice == 1)
            {
                pushCommand(PlayerCommand::Attack, now);
                continue;
            }

            //Spell selection range

            int spellStart = 2;
            int spellEnd   = spellStart + spells.size() - 1;

            if (choice >= spellStart && choice <= spellEnd)
            {
                int index = choice - spellStart;
                pushCommand(PlayerCommand::Spell, now, spells[index].getName());
                continue;
            }

            //Consumable range
            int itemStart = spellEnd + 1;
            int itemEnd   = itemStart + items.size() - 1;

            if (choice >= itemStart && choice <= itemEnd)
            {
                int index = choice - itemStart;
                pushCommand(PlayerCommand::Consumable, now, items[index].getName());
                continue;
            }

            std::cout << "[INVALID INPUT]\n";


        }
    }

    // ============================================================
    // COMBAT STATE
    // ============================================================

    void handleCommand(Player& player, NPC& enemy, const Command& cmd, float now)
    {
        switch (cmd.type)
        {
            case PlayerCommand::Attack:
                tryAttack(player, enemy, now);
                break;
            
            case PlayerCommand::Spell:
                tryCastSpell(player, enemy, cmd.data, now);
                break;
            
            case PlayerCommand::Consumable:
                tryUseConsumable(player, cmd.data, now);
                break

            default:
                break;
        }
    }

    void handleSpellCast(Entity* caster, float now)
    {
        if (!caster->cast.isCasting || caster->cast.spell == nullptr)
            return;

        Abilities* spell = caster.cast.spell;
        Entity* target = caster.cast.target;

        // finish spell cast
        spell->use(now);

        //Damage spell
        if (spell->isOffensive())
        {
            damage_t dmg = spell->rollDamage();
            if (caster.isCrit()) dmg *= 2;

            target->takeDamage(dmg);

            std::cout << caster.getEntityName() << " casts "
                        << spell->getName()
                        << " for " << dmg << " damage!\n";
        }
        else if (!(spell->isOffensive()))
        {
            damage_t heal = spell->rollDamage();
            if (caster.isCrit()) heal *= 2;

            caster->heal(heal);

            std::cout << caster.getEntityName() << " casts "
                        << spell->getName()
                        << " that heals themselves for " << heal << "\n";            
        }
        else
        {
            std::cout << caster->getEntityName()
                  << " finishes casting " << spell->getName() << ".\n";
        }

        
        //trigger gcd
        gcdEndTime = now + 1.5f;

        //Clear cast state
        caster.cast.isCasting = false;
        caster.cast.spell = nullptr;
        caster.cast.target = nullptr;
    }

    // ============================================================
    // COMBAT EXECUTION
    // ============================================================
    float gcdEndTime; //global cooldown timer

    void tryAttack(Player& player, NPC& enemy, float now)
    {
        if (now < gcdEndTime)
        {
            std::cout << "Attack on cooldown.\n";
            return;
        }

        player.attack(enemy, now);

        gcdEndTime = now + 1.5f; //1.5s GCD
    }

    void tryCastSpell(Player& player, NPC& enemy, const std::string& spellName, float now)
    {
        //Check GCD
        if (now < gcdEndTime)
        {
           std::cout << "[Fail] On Global Cooldown.\n";
            return;        
        }

        auto& spells = player.getAbilities();
        for (auto& sp: spells)
        {
            if (sp.getName() == spellName)
            {
                player.castSpell(&enemy, sp, now);
                return;
            }
        }
    
        std::cout << "[Fail] Spell not found.\n";
    }

    void tryUseConsumable(Player& player, const std::string& name, float now)
    {
            // Check GCD first
        if (now < gcdEndTime)
        {
            std::cout << "[Fail] On Global Cooldown.\n";
            return;
        }
        auto& items = player.inventory.getConsumables();

        for (auto& it : items)
        {
            if (it.getName() == name)
            {
                std::cout << "[Use] " << name << "\n";

                it.applyEffect(player);
                player.inventory.removeItem(it);

                gcdEndTime = now + 1.5f;
                return;
            }
        }
    }

};
