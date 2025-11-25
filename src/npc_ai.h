#pragma once
#include <vector>
#include <random>


enum class AIState{ Normal, Running };
class NPC;
class Player;
class NPC_AI
{
public:
    NPC_AI(NPC* controlledNPC, Player* target);
    void update(float currentTime);
    
private:
    NPC* npc;
    Player* player;
    AIState state;

    bool tryHeal(float time);

    bool tryPotion();

    bool tryCastOffensive(float time);

    float randFloat();

    bool chance(float p);

};
