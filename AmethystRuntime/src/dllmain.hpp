#pragma once
#include "AmethystRuntime.hpp"
#include <Windows.h>
#include <amethyst/Log.hpp>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main();
DWORD __stdcall EjectThread(LPVOID lpParameter);
void Shutdown();
void ShutdownWait();

extern "C" __declspec(dllexport) void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle);

LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo);