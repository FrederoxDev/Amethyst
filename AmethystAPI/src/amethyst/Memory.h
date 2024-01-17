#pragma once
#include "amethyst/Log.h"
#include <chrono>
#include <cstdint>
#include <psapi.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <windows.h>

template <typename Ret, typename Type>
Ret& direct_access(Type* type, size_t offset) {
    union {
        size_t raw;
        Type* source;
        Ret* target;
    } u;
    u.source = type;
    u.raw += offset;
    return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)       \
	AS_FIELD(type, name, get##name); \
	type get##name()

#define BUILD_ACCESS(ptr, type, name, offset)                           \
	AS_FIELD(type, name, get##name);                                    \
	type get##name() const { return direct_access<type>(ptr, offset); } \
	void set##name(type v) const { direct_access<type>(ptr, offset) = v; }

/*
Returns the position where Minecraft has been loaded into memory
*/
uintptr_t GetMinecraftBaseAddress();

/*
Returns the size of the game (in bytes) while loaded in memory
*/
unsigned long GetMinecraftSize();

/*
Offsets an address from the game binary, with the position the game has been loaded into memory at
*/
uintptr_t SlideAddress(uintptr_t offset);

/*
Finds an address of a function with its signature within the loaded game memory
*/
uintptr_t SigScan(std::string signature);

/**
 * Finds the offset of a pointer in a struct/class
 * returns SIZE_MAX if it fails
*/
size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize);
