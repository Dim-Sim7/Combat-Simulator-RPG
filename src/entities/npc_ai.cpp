#include "npc_ai.h"
#include "npc.h"
#include "player.h"
#include <iostream>
#include <cstdlib>

NPC_AI::NPC_AI(NPC* controlledNPC, Player* target)
    : npc(controlledNPC),
      player(target),
      state(AIState::Normal)
{
}

void NPC_AI::update(float currentTime)
{
    if (!npc || npc->isDead())
        return;

    if (npc->isOnGlobalCooldown(currentTime))
        return;

    float hpPct =
        static_cast<float>(npc->getCurrentHP()) /
        static_cast<float>(npc->getMaxHP());

    // ==============================
    // FLEE LOGIC
    // ==============================
    if (hpPct < 0.15f && state != AIState::Fleeing)
    {
        state = AIState::Fleeing;
        fleeStartTime = currentTime;
    }

    if (state == AIState::Fleeing)
    {
        std::cout << npc->getEntityName()
                  << " is almost dead!\n";

        if (currentTime - fleeStartTime > 2.5f ||
            chance(0.05f))
        {
            npc->escapeCombat();
            return;
        }

        // Cannot act while fleeing
        return;
    }

    // ==============================
    // HEALING LOGIC
    // ==============================
    if (hpPct <= 0.30f)
    {
        if (tryHeal(currentTime)) return;
        if (tryPotion(currentTime)) return;
    }

    // ==============================
    // OFFENSIVE LOGIC
    // ==============================
    float r = randFloat();

    if (r < 0.70f)
    {
        npc->attack(*player, currentTime);
    }
    else
    {
        tryCastOffensive(currentTime);
    }
}

// ======================================================
// HEAL SPELL
// ======================================================

bool NPC_AI::tryHeal(float time)
{
    for (const auto& spell : npc->getAbilities())
    {
        if (spell.getType() == ABILITYTYPE::HEAL)
        {
            npc->tryCastSpell(spell.getName(), npc, time);
            return true;
        }
    }

    return false;
}

// ======================================================
// POTION USE
// ======================================================

bool NPC_AI::tryPotion(float time)
{
    // Assumes "Healing Potion" exists in Entity consumable system
    return npc->tryUseConsumable("Healing Potion", time);
}

// ======================================================
// OFFENSIVE SPELL SELECTION
// ======================================================

bool NPC_AI::tryCastOffensive(float time)
{
    const Abilities* best = nullptr;

    for (const auto& spell : npc->getAbilities())
    {
        if (spell.getType() == ABILITYTYPE::HEAL)
            continue;

        if (!best ||
            spell.getAmountRange().second >
            best->getAmountRange().second)
        {
            best = &spell;
        }
    }

    if (!best)
        return false;

    npc->tryCastSpell(best->getName(), player, time);
    return true;
}

// ======================================================
// RNG
// ======================================================

float NPC_AI::randFloat()
{
    return static_cast<float>(rand()) / RAND_MAX;
}

bool NPC_AI::chance(float probability)
{
    return randFloat() < probability;
}
