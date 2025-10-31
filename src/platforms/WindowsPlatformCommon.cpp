#include "platforms/WindowsPlatformCommon.hpp"
#include <amethyst/Memory.hpp>
#include <debug/AmethystDebugging.hpp>
#include "loader/dllmain.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <DbgHelp.h>
#include <tchar.h>

WindowsPlatformCommon::WindowsPlatformCommon(HANDLE mcThreadHandle)
    : mMcThreadHandle(mcThreadHandle) {}

void WindowsPlatformCommon::AttachDebugger() const
{
    Log::Info("Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void WindowsPlatformCommon::PauseGameThread() const
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(mMcThreadHandle, NULL);
    Log::Info("Paused game thread!");
}

void WindowsPlatformCommon::ResumeGameThread() const
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(mMcThreadHandle, NULL);
    Log::Info("Resumed game thread!");
}

void WindowsPlatformCommon::InitializeConsole() const
{
    // The logger really needs to be platform independant
    // and it would be good if it supported writing to a file
    Log::InitializeConsole();
}

static const char* BaseNameA(const char* path) {
    if (!path || !*path) return "";
    const char* p = strrchr(path, '\\');
    const char* q = strrchr(path, '/');
    if (q && (!p || q > p)) p = q;
    return p ? (p + 1) : path;
}

std::string WideToAnsi(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(),
                                          nullptr, 0, nullptr, nullptr);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(),
                        strTo.data(), size_needed, nullptr, nullptr);
    return strTo;
}

void LogStackTrace(CONTEXT* context)
{
    if (!context) {
        Log::Error("[LogStackTrace] context is null");
        return;
    }

    HANDLE process = GetCurrentProcess();
    HANDLE thread  = GetCurrentThread();

    if (!SymInitialize(process, nullptr, TRUE)) {
        Log::Error("[LogStackTrace] SymInitialize failed: 0x{:X}", GetLastError());
        return;
    }

    STACKFRAME64 frame{};
    DWORD64 displacement = 0;
    DWORD machineType = IMAGE_FILE_MACHINE_AMD64;

    frame.AddrPC.Offset    = context->Rip;
    frame.AddrPC.Mode      = AddrModeFlat;
    frame.AddrFrame.Offset = context->Rbp;
    frame.AddrFrame.Mode   = AddrModeFlat;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrStack.Mode   = AddrModeFlat;

    Log::Error("Call Stack:");

    for (int i = 0; i < 128; ++i)
    {
        if (!StackWalk64(machineType, process, thread, &frame, context,
                         nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
            break;

        DWORD64 addr = frame.AddrPC.Offset;
        if (addr == 0) break;

        // Get module base for this address
        DWORD64 moduleBase = SymGetModuleBase64(process, addr);

        // Get module name (if we have a base)
        char moduleFullPath[MAX_PATH] = {0};
        if (moduleBase != 0) {
            HMODULE hMod = reinterpret_cast<HMODULE>(static_cast<uintptr_t>(moduleBase));
            if (!GetModuleFileNameA(hMod, moduleFullPath, MAX_PATH))
                moduleFullPath[0] = '\0';
        }
        const char* moduleBasename = BaseNameA(moduleFullPath);

        DWORD64 relativeAddr = moduleBase ? (addr - moduleBase) : addr;

        // Resolve symbol
        char symbolBuffer[sizeof(SYMBOL_INFO) + (MAX_SYM_NAME + 1) * sizeof(char)];
        PSYMBOL_INFO symbol = reinterpret_cast<PSYMBOL_INFO>(symbolBuffer);
        memset(symbolBuffer, 0, sizeof(symbolBuffer));
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen   = MAX_SYM_NAME;

        DWORD64 symDisplacement = 0;
        bool gotSymbol = SymFromAddr(process, addr, &symDisplacement, symbol) != 0;

        // Log frame
        if (moduleBase != 0) {
            if (gotSymbol) {
                Log::Error("    0x{:X} [{}] : {} + 0x{:X}",
                           relativeAddr,
                           moduleBasename[0] ? moduleBasename : "module_unknown",
                           symbol->Name, static_cast<unsigned long>(symDisplacement));
            } else {
                Log::Error("    0x{:X} [{}] : (unknown)",
                           relativeAddr, moduleBasename[0] ? moduleBasename : "module_unknown");
            }
        } else {
            if (gotSymbol) {
                Log::Error("    0x{:X} [no module] : {} + 0x{:X}", addr, symbol->Name, static_cast<unsigned long>(symDisplacement));
            } else {
                Log::Error("    0x{:X} [no module] : (unknown)", addr);
            }
        }

        // Optional: source line info
        IMAGEHLP_LINE64 lineInfo{};
        DWORD lineDisp = 0;
        lineInfo.SizeOfStruct = sizeof(lineInfo);
        if (SymGetLineFromAddr64(process, addr, &lineDisp, &lineInfo)) {
            Log::Error("        at {}:{}", lineInfo.FileName, lineInfo.LineNumber);
        }
    }

    SymCleanup(process);
}


LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo == nullptr) {
        std::cerr << "ExceptionInfo is nullptr" << std::endl;
        return ExceptionContinueSearch;
    }

	auto* record = ExceptionInfo->ExceptionRecord;
	auto* context = ExceptionInfo->ContextRecord;

	DWORD code = record->ExceptionCode;
	void* addr = record->ExceptionAddress;

	TCHAR moduleName[MAX_PATH] = {0};
	if (!GetModuleFileName(nullptr, moduleName, MAX_PATH)) {
		_tcscpy_s(moduleName, _T("UnknownModule"));
	}

	const char* exceptionName = "Unknown";
    switch (code)
    {
        case STILL_ACTIVE:                       exceptionName = "STILL_ACTIVE (STATUS_PENDING)"; break;
        case EXCEPTION_ACCESS_VIOLATION:         exceptionName = "Access Violation"; break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:    exceptionName = "Datatype Misalignment"; break;
        case EXCEPTION_BREAKPOINT:               exceptionName = "Breakpoint"; break;
        case EXCEPTION_SINGLE_STEP:              exceptionName = "Single Step"; break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    exceptionName = "Array Bounds Exceeded"; break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:     exceptionName = "Float Denormal Operand"; break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:       exceptionName = "Float Divide by Zero"; break;
        case EXCEPTION_FLT_INEXACT_RESULT:       exceptionName = "Float Inexact Result"; break;
        case EXCEPTION_FLT_INVALID_OPERATION:    exceptionName = "Float Invalid Operation"; break;
        case EXCEPTION_FLT_OVERFLOW:             exceptionName = "Float Overflow"; break;
        case EXCEPTION_FLT_STACK_CHECK:          exceptionName = "Float Stack Check"; break;
        case EXCEPTION_FLT_UNDERFLOW:            exceptionName = "Float Underflow"; break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:       exceptionName = "Integer Divide by Zero"; break;
        case EXCEPTION_INT_OVERFLOW:             exceptionName = "Integer Overflow"; break;
        case EXCEPTION_PRIV_INSTRUCTION:         exceptionName = "Privileged Instruction"; break;
        case EXCEPTION_IN_PAGE_ERROR:            exceptionName = "In Page Error"; break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:      exceptionName = "Illegal Instruction"; break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION: exceptionName = "Noncontinuable Exception"; break;
        case EXCEPTION_STACK_OVERFLOW:           exceptionName = "Stack Overflow"; break;
        case EXCEPTION_INVALID_DISPOSITION:      exceptionName = "Invalid Disposition"; break;
        case EXCEPTION_GUARD_PAGE:               exceptionName = "Guard Page Violation"; break;
        case EXCEPTION_INVALID_HANDLE:           exceptionName = "Invalid Handle"; break;
        // case EXCEPTION_POSSIBLE_DEADLOCK:        exceptionName = "Possible Deadlock"; break;
        case CONTROL_C_EXIT:                     exceptionName = "Control-C Exit"; break;
        default: break;
    }

	#ifdef _UNICODE
		std::string modNameStr = WideToAnsi(moduleName);
	#else
		std::string modNameStr = moduleName;
	#endif

	std::string modNameShort = BaseNameA(modNameStr.c_str());

	Log::Error("======== Unhandled {} Exception ========", exceptionName);
    Log::Error("  Module: {}", modNameShort);
    Log::Error("  Module Address: 0x{:X}",
        reinterpret_cast<uint64_t>(addr));
	Log::Error("  Minecraft Base Address: 0x{:X}",
		Amethyst::GetPlatform().GetMinecraftBaseAddress());
    Log::Error("  Error Code: 0x{:08X} ({})", code, exceptionName);

	Log::Error("");

	LogAssemblyOfExceptionCause(reinterpret_cast<uint64_t>(addr));

	Log::Error("");

	LogStackTrace(context);

	auto& platform = Amethyst::GetPlatform();
    platform.ShutdownWaitForInput();

	return ExceptionContinueSearch;	
}

void WindowsPlatformCommon::Initialize()
{
    SetUnhandledExceptionFilter(AmethystUnhandledExceptionsHandler);
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    ExitProcess(0);
}

void WindowsPlatformCommon::Shutdown()
{
    auto& rt = AmethystRuntime::GetInstance();
    rt.Shutdown();

    Log::DestroyConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void WindowsPlatformCommon::ShutdownWaitForInput()
{
    Log::Info("Press Numpad0/End to close...");

    while (1) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
}

bool WindowsPlatformCommon::HasRequestedStop() const
{
    return GetAsyncKeyState(VK_NUMPAD0) || GetAsyncKeyState(VK_END);
}

bool WindowsPlatformCommon::HasRequestedHotReload() const
{
    return GetAsyncKeyState('R') & 0x8000;
}