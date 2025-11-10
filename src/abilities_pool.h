#include "abilities.h"
#include <vector>
#include <random>
#include <algorithm>
//holds all player abilities
//getrandomability
//has abiliti

class AbiltiesPool {
public:
    AbilitiesPool() {
        loadAllAbilities();
    }

    //Return a random ability that the player doesn't own
    Abilities getRandomAbility(const std::vector<Abilities>& ownedAbilities) const {
        std::vector<Abilities> available;

        for (const auto& ability : allAbilities) { //const (promise not to change), auto(infer type automatically at compile time), &(bind by  reference, no copy of object)
            if (!hasAbility(ability, ownedAbilities)) {
                available.push_back(ability);
            }
        }

        if (available.empty()) {
            //if all abilities are learned
            return Abilities("None", {0, 0}, 0, 0, 0, ability_t::INSTANT);
        }

        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<size_t> dist(0, available.size() - 1);
        return available[dist(gen)];
    }
private:
    std::vector<Abilities> allAbilities;

    void loadAllAbilities() {
        allAbilities = {
            Abilities("Fireball", {100, 150}, 3, 2, 50, ability_t::CAST),
            Abilities("Frostbolt", {80, 120}, 2, 2, 40, ability_t::CAST),
            Abilities("Arcane Missiles", {50, 60}, 5, 5, 60, ability_t::CHANNEL),
            Abilities("Ice Lance", {40, 70}, 1, 0, 20, ability_t::INSTANT),
            Abilities("Renew", {100, 120}, 6, 2, 30, ability_t::HEAL),
            Abilities("Corruption", {60, 100}, 3, 2, 35, ability_t::DOT),
        };
    }

    bool hasAbility(const Abilities& ability, const std::vector<Abilities>& owned) const {
    return std::any_of(owned.begin(), owned.end(),
        [&](const Abilities& a) { return a.getName() == ability.getName(); });
    }
};
