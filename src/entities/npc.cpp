#include "npc.h"

NPC::NPC() : Entity() {}

NPC::NPC(const StatBlock& statsInit, 
            int hpInitCurr, 
            int hpInitMax, 
            const std::vector<Abilities>& abilitiesInit,
            const std::string& nameInit)
            : Entity(statsInit, hpInitMax, hpInitCurr, abilitiesInit, nameInit)
            {}

NPC::hasPotion() const {
    
}