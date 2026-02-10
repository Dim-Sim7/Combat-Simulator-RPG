#pragma once

#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <memory>
#include <string>

#include "entities/npc_ai.h"
#include "player.h"
#include "npc.h"
#include "item.h"
#include "inventory.h"

enum class PlayerCommand { Attack, Spell, Consumable, Run, None };

struct Command {
    PlayerCommand type = PlayerCommand::None;
    std::string data;
    float timestamp;
};

class BattleSystem
{
public:
    BattleSystem();
    ~BattleSystem();

    void battleLoop(Player& player, NPC& enemy);

private:
    std::unique_ptr<NPC_AI> enemyAI;

    std::chrono::steady_clock::time_point startTime;
    float gcdEndTime;

    float getTime();

    std::mutex commandMutex;
    std::queue<Command> commandQueue;

    void pushCommand(PlayerCommand command, float currentTime, const std::string& data = "");
    bool popCommand(Command& out);

    std::atomic<bool> running;
    std::thread inputThread;

    void inputLoop(Player& player);

    void handleCommand(Player& player, NPC& enemy, const Command& cmd, float now);
    void handleSpellCast(Entity* caster, float now);

    void tryAttack(Player& player, NPC& enemy, float now);
    void tryCastSpell(Player& player, NPC& enemy, const std::string& spellName, float now);
    void tryUseConsumable(Player& player, const std::string& name, float now);

    void applyConsumableEffect(Player* player, const StatModifier& statMod);
};
