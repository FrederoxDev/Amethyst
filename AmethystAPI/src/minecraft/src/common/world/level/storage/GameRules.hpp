#pragma once
#include <amethyst/Memory.hpp>

class GameRule {
public:
    /* this + 0 */ std::byte padding0[8];
    /* this + 8 */ std::string mName;
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