#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "amethyst/Log.hpp"

#include "loader/AmethystRuntime.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main();
DWORD __stdcall EjectThread(LPVOID lpParameter);

/**
 * Contract with Amethyst-Preload. Must match preload/src/dllmain.hpp in the launcher: the
 * preload refuses to start a runtime whose ABI it does not recognise, which is what keeps a
 * mismatched pair from running rather than crashing.
 */
#define AMETHYST_PRELOAD_ABI 1

struct AmethystPreloadInfo {
    uint32_t abi;
    const wchar_t* gameDir;
    const char* sessionJson;
};

#ifdef WIN_CLIENT
/**
 * Called by the preload on Minecraft's own main thread, after the loader has released its lock
 * and before the game's entry point runs. Nothing is suspended and nothing may be: this returns
 * so the game can start.
 *
 * Replaces the old Init(threadId, threadHandle), which took a suspended main thread and made
 * the runtime responsible for resuming it. The thread it created to do that could not start
 * until it acquired the loader lock, which the suspended thread was often holding - so roughly
 * one launch in ten hung with neither thread able to proceed.
 */
extern "C" __declspec(dllexport) void __cdecl AmethystRuntimeStart(const AmethystPreloadInfo* info);
#endif

#ifdef WIN_SERVER
extern "C" __declspec(dllexport) DWORD __cdecl ServerInit(LPVOID lp);
#endif

LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo);