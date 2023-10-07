#pragma once
#include <Windows.h>
#include "MinHook.h"
#include "Log.h"
//#include "Mod.h"
#pragma comment(lib, "libMinHook.x64.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main();
DWORD __stdcall EjectThread(LPVOID lpParameter);
void Shutdown();
void ShutdownWait();