#include "dllmain.hpp"
#include "debug/AmethystDebugging.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include <thread>
#include "platforms/WindowsClientPlatform.hpp"
#include "platforms/WindowsServerPlatform.hpp"

HMODULE hModule;
HANDLE gMcThreadHandle;
DWORD gMcThreadId;

extern AmethystContext* _AmethystContextInstance;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    ::hModule = hModule;
    return TRUE;
}

DWORD WINAPI Main()
{
	#ifdef WIN_CLIENT
    auto _platform = std::make_unique<WindowsClientPlatform>(gMcThreadHandle);
	#endif

	#ifdef WIN_SERVER
    auto _platform = std::make_unique<WindowsServerPlatform>(gMcThreadHandle);
	#endif

    AmethystRuntime* runtime = new AmethystRuntime(std::move(_platform));

    // Initialize AmethystContextInstance so Amethyst::GetXYZ functions work.
    _AmethystContextInstance = &runtime->mAmethystContext;

    auto& platform = Amethyst::GetPlatform();
    platform.Initialize(); // Initialize things like uncaught exception handling

    platform.InitializeConsole();
    Log::InitializeFileLogging();

    // Returns rather than parking: this runs on Minecraft's own main thread, before the game's
    // entry point, so the game only starts once this call comes back. The wait is kept for the
    // failure path alone, where there is something for the user to read.
    try {
        runtime->Start();
    }
    catch (std::exception& exception) {
        Log::Error("Uncaught Exception: {}", exception.what());
        platform.ShutdownWaitForInput();
        return 1;
    }

    // Only now, with the game about to start and nothing suspended, is creating a thread safe.
    std::thread([runtime] { runtime->WatchForHotReload(); }).detach();
    return 0;
}

#ifdef WIN_CLIENT
void __cdecl AmethystRuntimeStart(const AmethystPreloadInfo* info)
{
    if (info == nullptr || info->abi != AMETHYST_PRELOAD_ABI) {
        Log::Error("Amethyst-Preload speaks ABI {}, this runtime speaks {}. Update whichever is older.",
                   info == nullptr ? 0 : info->abi, AMETHYST_PRELOAD_ABI);
        return;
    }

    // The game's main thread is the one running this, so its handle is taken here rather than
    // handed over. Kept because hot reloading and the debugger attach still want it; the
    // startup path no longer suspends anything.
    gMcThreadId = GetCurrentThreadId();
    gMcThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, gMcThreadId);

    Main();
}
#endif

#ifdef WIN_SERVER
/** The server is injected by its own preloader, which still hands the thread over this way. */
struct ThreadData {
    DWORD  dwThreadId;
    HANDLE hThreadHandle;
};

extern "C" __declspec(dllexport) DWORD WINAPI ServerInit(LPVOID lp)
{
	ThreadData* td = static_cast<ThreadData*>(lp);
    gMcThreadHandle = td->hThreadHandle;
    gMcThreadId     = td->dwThreadId;
	Main();

	return 0;
}
#endif