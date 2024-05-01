#pragma once
#include "amethyst/Log.hpp"
#include <chrono>
#include <cstdint>
#include <psapi.h>
#include <cstdint>
#include <string>
#include <vector>
#include <Windows.h>
#include <string_view>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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
std::optional<uintptr_t> SigScanSafe(std::string_view signature);

/*
Finds an address of a function with its signature within the loaded game memory
*/
uintptr_t SigScan(std::string_view signature);

/**
 * Finds the offset of a pointer in a struct/class
 * returns SIZE_MAX if it fails
*/
size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize);

/**
 * Unprotects the memory region 
*/
void UnprotectMemory(uintptr_t address, size_t size, DWORD* oldProtection);

/**
 * Reprotects the memory region
*/
void ProtectMemory(uintptr_t address, size_t size, DWORD protectionData, DWORD* oldProtection = nullptr);

/*
 * Returns the offset (in loaded memory space), to a pointer in a lea instruction
 */
uintptr_t AddressFromLeaInstruction(uintptr_t leaInstructionAddress);