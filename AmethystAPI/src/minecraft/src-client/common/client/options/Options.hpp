#pragma once
#include <vector>
#include <memory>
#include <array>
#include <minecraft/src-client/common/client/options/BaseOptions.hpp>
#include <minecraft/src-client/common/client/input/KeyboardRemappingLayout.hpp>

class Option;

class Options : public std::enable_shared_from_this<Options>, public BaseOptions {
public:
    /* this + 24   */ std::array<std::unique_ptr<Option>, 738> mOptions;
    /* this + 5928 */ std::byte padding5928[6256 - 5928];
    /* this + 6256 */ std::vector<std::shared_ptr<KeyboardRemappingLayout>> mKeyboardRemappings;

    // 1.21.0.3 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F8 4C 89 44 24 ? 48 8B F1
    // Fake ctor hook target
    void _Options(void*, void*, void*, void*, char, void*, void*);
};

static_assert(offsetof(Options, mKeyboardRemappings) == 6256);
//static_assert(sizeof(Options) == 6424);