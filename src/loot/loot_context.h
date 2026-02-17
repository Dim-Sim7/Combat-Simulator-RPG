#pragma once

#include "rng.h"
#include <optional>
enum class EnemyTier {
    Normal,
    Elite,
    Boss
};


inline float tierScale(EnemyTier tier) {
    switch (tier) {
        case EnemyTier::Normal: return 1.0f;
        case EnemyTier::Elite:  return 1.2f;
        case EnemyTier::Boss:   return 1.5f;
    }
    return 1.0f;
}

inline float levelScale(int level) {
    return 1.0f + (level - 1) * 0.05f;
}


struct LootContext {
    int level; //level of loot source
    EnemyTier enemyTier;   // Normal / Elite / Boss
    RNG& rng;
    //OPTIONAL
    std::optional<int> chestTier;
};
