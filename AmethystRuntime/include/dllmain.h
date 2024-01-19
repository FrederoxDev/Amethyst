#pragma once
#include "AmethystRuntime.h"
#include <Windows.h>
#include <amethyst/Log.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main(DWORD dMcThreadID, HANDLE hMcThreadHandle);
DWORD __stdcall EjectThread(LPVOID lpParameter);
void Shutdown();
void ShutdownWait();
extern "C" __declspec(dllexport) void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle);

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo);