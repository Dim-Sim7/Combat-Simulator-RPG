enum class EnemyTier {
    Normal,
    Elite,
    Boss
};


struct LootContext {
    int level; //level of loot source
    EnemyTier enemyTier;   // Normal / Elite / Boss
    RNG& rng;
    //OPTIONAL
    std::optional<int> chestTier;
};
