#pragma once
#include "npc.h"
#include <vector>
#include <random>

enum class AIState{ Normal, Running };

class NPC_AI
{
public:
    NPC_AI(NPC* controlledNPC, Player* target)
        : npc(controlledNPC), player(target), state(AIState::Normal) {}
    
    void update(float currentTime)
    {
        if (!npc || npc->isDead()) return;

        float hpPct = npc->getCurrentHP() / npc->getMaxHP();

        //escape logic
        if (hpPct < 0.15f)
            state = AIState::Running;
        
        if (state == AIState::Running)
        {
            if (chance(0.05f))
            {
                npc->escapeCombat();
                return;
            }
            // Cannot act while running
            return;
        }

        //healing logic
        if (hpPct < 0.30f)
        {
            if (tryHeal(currentTime)) return;
            if (tryPotion()) return;
        }

        // Offensive logic

        float r = randFloat();

        if (r < 0.70f)
            npc->attack(*player, currentTime);
        else
            tryCastOffensive(currentTime);
    }
    
private:
    NPC* npc;
    Player* player;
    AIState state;

    bool tryHeal(float time)
    {
        for (auto& spell : npc->getAbilities())
        {
            if(spell.getType() == ABILITYTYPE::HEAL && spell.isOffCD(time))
            {
                npc->castSpell(npc, spell, time);
                return true;
            }
        }
        return false;
    }

    bool tryPotion()
    {
        if (npc->hasPotion())
        {
            npc->usePotion();
            return true;
        }
        return false;
    }

    bool tryCastOffensive(float time)
    {
        std::vector<Abilities*> available;

        for (auto* spell: npc->getAbilities())
        {
            if (spell.getType() != ABILITYTYPE::HEAL && spell.isOffCD(time))
                available.push_back(&spell);
        }

        if (available.empty())
            return false;

        int index = rand() % available.size();
        Abilities* chosenSpell = available[index];

        npc->castSpell(player, *chosenSpell, time);
        return true;
    }

    float randFloat()
    {
        return static_cast<float>(rand()) / RAND_MAX;
    }

    bool chance(float p)
    {
        return randFloat() < p;
    }

};
