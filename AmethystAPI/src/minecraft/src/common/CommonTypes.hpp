#pragma once
#include <cstdint>
#include <minecraft/src/common/util/NewType.hpp>

struct Brightness : public NewType<unsigned char> {
public:
    const static Brightness MAX;
};

struct BrightnessPair {
    Brightness sky;
    Brightness block;
};

using Height = short;

enum class SubClientId : unsigned char {
	PrimaryClient, 
	Client2, 
	Client3, 
	Client4, 
	ExtraIdSlotStart = 100, 
	EditorUI
};

typedef uint32_t BlockRuntimeId;