#pragma once
#include <stdint.h>
#include <windows.h>
#include <psapi.h>
#include <string>
#include <cstdint>
#include <chrono>
#include <vector>
#include "amethyst/Log.h"

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