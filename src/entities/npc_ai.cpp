#include "npc_ai.h"
#include "player.h"
#include "npc.h"
#include "../loot/rng.h"
NPC_AI::NPC_AI(NPC* controlledNPC, Player* target)
    : npc(controlledNPC), player(target), state(AIState::Normal) {}

void NPC_AI::update(float currentTime)
{
    if (!npc || npc->isDead()) return;

    float hpPct = static_cast<float>(npc->getHP().getCurrent()) / npc->getHP().getMax();

    //escape logic
    if (hpPct < 0.15f && state != AIState::Fleeing)
    {
        state = AIState::Fleeing;
        fleeStartTime = currentTime;
    }
        
    
    if (state == AIState::Fleeing)
    {
        std::cout << npc->getEntityName() << " is almost dead!\n";
        if (currentTime - fleeStartTime > 2.5f || chance(0.05f))
        {
            npc->escapeCombat();0
            return;
        }
        // Cannot act while Fleeing
        continue;
    }

    //healing logic
    if (hpPct <= 0.30f)
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
    Abilities* best = nullptr;

    for (auto& spell: npc->getAbilities())
    {
        if (spell.getType() == ABILITYTYPE::HEAL)
            continue;

        if (!spell.isOffCD(time))
            continue;
        
        if (!best || spell.getDamageRange().second > best->getDamageRange().second)
            best = &spell;
    }

    if (!best)
        return false;
    
    npc->castSpell(player, *best, time);
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

