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

    AmethystRuntime* runtime = new AmethystRuntime(std::move(_platform), std::this_thread::get_id());

    // Initialize AmethystContextInstance so Amethyst::GetXYZ functions work.
    _AmethystContextInstance = &runtime->mAmethystContext;

    auto& platform = Amethyst::GetPlatform();
    platform.Initialize(); // Initialize things like uncaught exception handling

    try {
        runtime->Start();
    }
    catch (std::exception& exception) {
        Log::Error("Uncaught Exception: {}", exception.what());
        throw exception;
    }

    platform.ShutdownWaitForInput();
    return 0;
}

struct ThreadData {
    DWORD  dwThreadId;
    HANDLE hThreadHandle;
};

#ifdef WIN_CLIENT
void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle)
{
    ThreadData* pData = new ThreadData;
    pData->dwThreadId = dMcThreadID;
    pData->hThreadHandle = hMcThreadHandle;

    auto mainCallLambda = [](LPVOID lpParameter) -> DWORD {
        // Cast the parameter back to ThreadData
        auto pData = static_cast<ThreadData*>(lpParameter);
        gMcThreadHandle = pData->hThreadHandle;
        gMcThreadId = pData->dwThreadId;

        DWORD result = Main();

        // Return the result
        delete pData;
        return result;
    };

    // Create the thread and pass the lambda function and the ThreadData struct
    CreateThread(nullptr, 0, mainCallLambda, pData, 0, nullptr);
}
#endif

#ifdef WIN_SERVER
extern "C" __declspec(dllexport) DWORD WINAPI ServerInit(LPVOID lp)
{
	ThreadData* td = static_cast<ThreadData*>(lp);
    gMcThreadHandle = td->hThreadHandle;
    gMcThreadId     = td->dwThreadId;
	Main();

	return 0;
}
#endif