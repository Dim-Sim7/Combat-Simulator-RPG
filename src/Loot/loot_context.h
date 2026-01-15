enum class EncounterType {
    Normal,
    Elite,
    Boss
};

enum class LocationType {
    Overworld,
    Dungeon
};

struct LootContext {
    int level; //level of loot source
    MobType mobType; //humanoids drop more gold

    EncounterType encounterType;   // Normal / Elite / Boss
    LocationType locationType;     // Overworld / Dungeon

    //OPTIONAL
    std::optional<int> chestTier;
};
