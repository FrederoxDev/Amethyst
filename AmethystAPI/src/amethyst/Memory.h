#pragma once
#include "amethyst/Log.h"
#include <chrono>
#include <cstdint>
#include <psapi.h>
#include <cstdint>
#include <string>
#include <vector>
#include <Windows.h>
#include <string_view>

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
uintptr_t SigScan(std::string_view signature);

/**
 * Finds the offset of a pointer in a struct/class
 * returns SIZE_MAX if it fails
*/
size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize);

template <typename Ret, typename Type>
typename std::conditional<std::is_const<Type>::value, std::add_const<Ret>, std::remove_const<Ret>>::type&
DirectAccess(Type* type, size_t offset) {
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
	type& get##name()

#define BUILD_ACCESS(ptr, type, name, offset)                           \
	AS_FIELD(type, name, get##name);                                    \
	type& get##name() const { return DirectAccess<type>(ptr, offset); } \
	void set##name(type v) const { DirectAccess<type>(ptr, offset) = std::move(v); }