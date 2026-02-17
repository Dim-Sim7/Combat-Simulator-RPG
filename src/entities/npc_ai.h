#pragma once

#include <string>

class NPC;
class Player;

enum class AIState
{
    Normal,
    Fleeing
};

class NPC_AI
{
public:
    NPC_AI(NPC* controlledNPC, Player* target);

    void update(float currentTime);

private:
    bool tryHeal(float time);
    bool tryPotion(float time);
    bool tryCastOffensive(float time);

    float randFloat();
    bool chance(float probability);

private:
    NPC* npc;
    Player* player;

    AIState state;
    float fleeStartTime = 0.0f;
};
