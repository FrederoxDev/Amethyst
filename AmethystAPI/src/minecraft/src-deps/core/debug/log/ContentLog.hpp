#pragma once
#include <cstdint>
#include "amethyst/Memory.hpp"

enum class LogLevel : unsigned int {
    Verbose = 0,
    Inform = 1,
    Warning = 2,
    Error = 3,
    _COUNT = 4,
};

// Note the old ones we found from 1.19 are out of date
enum class LogArea : unsigned int {
    Actor = 0,
    Addon = 1,
    AI = 2,
    Animation = 3,
    AutomatedTests = 4,
    BiomeRegistry = 5,
    Blocks = 6,
    Camera = 7,
    Commands = 8,
    Components = 9,
    Dialogue = 10,
    Effects = 11,
    Entity = 12,
    FeatureRegistry = 13,
    Geometry = 14,
    Item = 15,
    Json = 16,
    LevelStorage = 17,
    Lightning = 18,
    Localization = 19,
    Log = 20,
    Molang = 21,
    Messaging = 22,
    Recipes = 23,
    Rendering = 24,
    RuntimeCamera = 25,
    Scripting = 26,
    Sound = 27,
    Store = 28,
    Structure = 29,
    Texture = 30,
    TexturUI = 31,
    Volumes = 32,
    LootTable = 33,
    Packs = 34,
    _COUNT = 35,
};

// Constructor Signature "48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F9 48 8D 05 ? ? ? ? 48 89 01 48 89 4C 24 ? 48 83 C1 ? 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 07 C6 47"

class ContentLog {
public:
    uintptr_t** vtable;

    template<typename... Strings>
    int Log(bool doNotRepeat, LogLevel logLevel, LogArea logArea, Strings... strings) {
        using function = int (ContentLog::*)(bool, LogLevel, LogArea, Strings...);
        auto func = std::bit_cast<function>(SigScan("44 89 4C 24 ? 48 83 EC"));
        return (this->*func)(doNotRepeat, logLevel, logArea, strings...);
    }
};