#pragma once
#include "AmethystRuntime.h"
#include <Windows.h>
#include <amethyst/Log.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main();
DWORD __stdcall EjectThread(LPVOID lpParameter);
void Shutdown();
void ShutdownWait();