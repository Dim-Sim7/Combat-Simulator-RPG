#include "npc_ai.h"
#include "player.h"
#include "npc.h"
NPC_AI::NPC_AI(NPC* controlledNPC, Player* target)
    : npc(controlledNPC), player(target), state(AIState::Normal) {}

void NPC_AI::update(float currentTime)
{
    if (!npc || npc->isDead()) return;

    float hpPct = static_cast<float>(npc->getHP().getCurrent()) / npc->getHP().getMax();

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
        npc->attack(static_cast<Entity&>(*player), currentTime);
    else
        tryCastOffensive(currentTime);
}
    


bool NPC_AI::tryHeal(float time)
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

bool NPC_AI::tryPotion()
{
    if (npc->hasPotion())
    {
        npc->usePotion();
        return true;
    }
    return false;
}

bool NPC_AI::tryCastOffensive(float time)
{
    std::vector<Abilities*> available;

    for (auto& spell: npc->getAbilities())
    {
        if (spell.getType() != ABILITYTYPE::HEAL && spell.isOffCD(time))
            available.push_back(&spell);
    }

    if (available.empty())
        return false;

    int index = rand() % available.size();
    Abilities* chosenSpell = available[index];

    npc->castSpell(static_cast<Entity*>(player), *chosenSpell, time);
    return true;
}

float NPC_AI::randFloat()
{
    return static_cast<float>(rand()) / RAND_MAX;
}

bool NPC_AI::chance(float p)
{
    return randFloat() < p;
}

