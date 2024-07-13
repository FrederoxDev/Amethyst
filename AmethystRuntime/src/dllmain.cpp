#include "dllmain.hpp"
#include <debug/AmethystDebugging.hpp>

HANDLE gMcThreadHandle;
DWORD gMcThreadId;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo == nullptr) {
        std::cerr << "ExceptionInfo is nullptr" << std::endl;
        return ExceptionContinueSearch;
    }

    HMODULE hModule = GetModuleHandle(nullptr);

    TCHAR szModuleName[MAX_PATH];
    GetModuleFileName(hModule, szModuleName, MAX_PATH);

    EXCEPTION_RECORD* exceptionRecord = ExceptionInfo->ExceptionRecord;
    uint64_t exceptionAddr = (uint64_t)exceptionRecord->ExceptionAddress;
    uint64_t exceptionCode = (uint64_t)exceptionRecord->ExceptionCode;

    Log::Error("[AmethystRuntime] Exception thrown at 0x{:x}\n", exceptionAddr - GetMinecraftBaseAddress(), szModuleName);
    LogAssemblyOfExceptionCause(exceptionAddr);
    Log::Error("\nError Code: 0x{:x}", exceptionCode);

    ShutdownWait();
    return ExceptionContinueSearch;
}

DWORD WINAPI Main()
{
    Log::InitializeConsole();
    SetUnhandledExceptionFilter(AmethystUnhandledExceptionsHandler);

    // Create an instance of AmethystRuntime and invoke it to start
    AmethystRuntime* runtime = AmethystRuntime::getInstance();

    try {
        runtime->Start();
    }
    catch (std::exception& exception) {
        Log::Error("[AmethystRuntime] Uncaught Exception: {}", exception.what());
        throw exception;
    }

    ShutdownWait();
    return 0;
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    ExitProcess(0);
}

void Shutdown()
{
    AmethystRuntime* runtime = AmethystRuntime::getInstance();
    runtime->Shutdown();

    Log::DestroyConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void ShutdownWait()
{
    Log::Info("Press Numpad0 to close...");

    while (1) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
}

void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle)
{
    // Define a struct to hold the data
    struct ThreadData {
        DWORD dwThreadId;
        HANDLE hThreadHandle;
    };

    // Create an instance of the ThreadData struct
    ThreadData* pData = new ThreadData;
    pData->dwThreadId = dMcThreadID;
    pData->hThreadHandle = hMcThreadHandle;

    auto mainCallLambda = [](LPVOID lpParameter) -> DWORD {
        // Cast the parameter back to ThreadData
        auto pData = static_cast<ThreadData*>(lpParameter);
        Log::Info("[AmethystRuntime] McThreadID: {}, McThreadHandle: {}", pData->dwThreadId, pData->hThreadHandle);
        
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
