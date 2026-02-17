#pragma once

#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <memory>
#include <string>

#include "entities/npc_ai.h"
#include "entities/player.h"
#include "entities/npc.h"


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


};
