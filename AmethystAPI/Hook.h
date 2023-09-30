#pragma once
#include <cstdint>
#include <Windows.h>
#include "MinHook.h"
#include "Log.h"

uintptr_t GetMinecraftBaseAddress();
uintptr_t SlideAddress(uintptr_t offset);

template <typename T>
void CreateHook(uintptr_t targetAddress, void* detour, T& original) {
    LPVOID address = reinterpret_cast<LPVOID>(targetAddress);

    MH_STATUS status = MH_CreateHook(address, detour, reinterpret_cast<LPVOID*>(&original));
    if (status != MH_OK) {
        Log::Error("MH_CreateHook failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }

    status = MH_EnableHook(address);
    if (status != MH_OK) {
        Log::Error("MH_EnableHook failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }
}