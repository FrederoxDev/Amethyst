#pragma once
#include <amethyst/Memory.hpp>

enum GameRulesIndex {
    CommandBlockOutput = 0,
    DoDayLightCycle = 1,
    DoEntityDrops = 2,
    DoFireTick = 3,
    RecipesUnlock = 4,
    DoLimitedCrafting = 5,
    DoMobLoot = 6,
    DoMobSpawning = 7,
    DoTileDrops = 8,
    DoWeatherCycle = 9,
    DrowningDamage = 10,
    FallDamage = 11,
    FireDamage = 12,
    KeepInventory = 13,
    MobGriefing = 14,
    PvP = 15,
    ShowCoordinates = 16,
    ShowDaysPlayed = 17,
    NaturalRegeneration = 18,
    TntExplodes = 19,
    SendCommandFeedback = 20,
    MaxCommandChainLength = 21,
    DoInsomnia = 22,
    CommandBlocksEnabled = 23,
    RandomTickSpeed = 24,
    DoImmediateRespawn = 25,
    ShowDeathMessages = 26,
    FunctionCommandLimit = 27,
    SpawnRadius = 28,
    ShowTags = 29,
    FreezeDamage = 30,
    RespawnBlocksExplode = 31,
    ShowBorderEffect = 32,
    ShowRecipeMessages = 33,
    PlayersSleepingPercentage = 34,
    ProjectilesCanBreakBlocks = 35,
    TntExplosionDropDecay = 36,
};

class GameRule {
public:
    /* this + 0  */ std::byte padding0[4];
    /* this + 4  */ bool mEnabled;
    /* this + 5  */ std::byte padding5[3];
    /* this + 8  */ std::string mName;
    /* this + 40 */ std::byte padding40[3];
    /* this + 43 */ bool mRequiresCheats;
    /* this + 44 */ std::byte padding44[132];
};

class GameRules {
public:
    /* this + 0  */ std::byte padding0[24];
    /* this + 24 */ std::vector<GameRule> mGamerules;

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F9 48 83 C1
    void _registerRules();
};