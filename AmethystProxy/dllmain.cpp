#pragma once

#pragma comment(linker,"/export:WldpAddDeveloperCertificateForDynamicCodeTrust=C:\\Windows\\System32\\wldp.WldpAddDeveloperCertificateForDynamicCodeTrust,@5")
#pragma comment(linker,"/export:WldpCheckDeviceEncryptionNotStarted=C:\\Windows\\System32\\wldp.WldpCheckDeviceEncryptionNotStarted,@6")
#pragma comment(linker,"/export:WldpCheckRetailConfiguration=C:\\Windows\\System32\\wldp.WldpCheckRetailConfiguration,@7")
#pragma comment(linker,"/export:WldpCheckSecurityWatermarkState=C:\\Windows\\System32\\wldp.WldpCheckSecurityWatermarkState,@8")
#pragma comment(linker,"/export:WldpCheckWcosDeviceEncryptionSecure=C:\\Windows\\System32\\wldp.WldpCheckWcosDeviceEncryptionSecure,@9")
#pragma comment(linker,"/export:WldpDisableDeveloperMode=C:\\Windows\\System32\\wldp.WldpDisableDeveloperMode,@10")
#pragma comment(linker,"/export:WldpEnableDeveloperMode=C:\\Windows\\System32\\wldp.WldpEnableDeveloperMode,@11")
#pragma comment(linker,"/export:WldpGetLockdownPolicy=C:\\Windows\\System32\\wldp.WldpGetLockdownPolicy,@12")
#pragma comment(linker,"/export:WldpIsAllowedEntryPoint=C:\\Windows\\System32\\wldp.WldpIsAllowedEntryPoint,@13")
#pragma comment(linker,"/export:WldpIsAppApprovedByPolicy=C:\\Windows\\System32\\wldp.WldpIsAppApprovedByPolicy,@1")
#pragma comment(linker,"/export:WldpIsClassInApprovedList=C:\\Windows\\System32\\wldp.WldpIsClassInApprovedList,@14")
#pragma comment(linker,"/export:WldpIsDebugAllowed=C:\\Windows\\System32\\wldp.WldpIsDebugAllowed,@15")
#pragma comment(linker,"/export:WldpIsDynamicCodePolicyEnabled=C:\\Windows\\System32\\wldp.WldpIsDynamicCodePolicyEnabled,@16")
#pragma comment(linker,"/export:WldpQueryDynamicCodeTrust=C:\\Windows\\System32\\wldp.WldpQueryDynamicCodeTrust,@17")
#pragma comment(linker,"/export:WldpQuerySecurityPolicy=C:\\Windows\\System32\\wldp.WldpQuerySecurityPolicy,@18")
#pragma comment(linker,"/export:WldpQueryWindowsLockdownMode=C:\\Windows\\System32\\wldp.WldpQueryWindowsLockdownMode,@2")
#pragma comment(linker,"/export:WldpQueryWindowsLockdownRestriction=C:\\Windows\\System32\\wldp.WldpQueryWindowsLockdownRestriction,@3")
#pragma comment(linker,"/export:WldpResetSecurityWatermarkState=C:\\Windows\\System32\\wldp.WldpResetSecurityWatermarkState,@19")
#pragma comment(linker,"/export:WldpSetDynamicCodeTrust=C:\\Windows\\System32\\wldp.WldpSetDynamicCodeTrust,@20")
#pragma comment(linker,"/export:WldpSetDynamicCodeTrust2=C:\\Windows\\System32\\wldp.WldpSetDynamicCodeTrust2,@21")
#pragma comment(linker,"/export:WldpSetWindowsLockdownRestriction=C:\\Windows\\System32\\wldp.WldpSetWindowsLockdownRestriction,@4")

#include "windows.h"
#include "ios"
#include "fstream"
#include "filesystem"
#include <shlobj_core.h>
#include <amethyst/Config.h>



// Define the NtSuspendThread function signature
typedef NTSTATUS(NTAPI* NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
// Define the NtResumeThread function signature
typedef NTSTATUS(NTAPI* NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);

// Define the Amethyst Init function signature
typedef void(__cdecl* AmethystInitPtr)(DWORD dMcThreadID, HANDLE hMcThreadHandle);
    

// Remove this line if you aren't proxying any functions.
HMODULE hProxied = LoadLibrary(L"C:\\Windows\\System32\\wldp.dll");
HMODULE hAmethyst = NULL;

HMODULE hClientModule = NULL;

DWORD dMcThreadID = NULL;
HANDLE hMcThreadHandle = NULL;

// Define the NtSuspendThread function pointer
NtSuspendThreadPtr NtSuspendThread = NULL;
// Define the NtResumeThread function pointer
NtResumeThreadPtr NtResumeThread = NULL;
// Define the Amethyst Init function pointer
AmethystInitPtr AmethystInit = NULL;

#pragma warning(disable: 4996)
#include "iostream"

Config loadConfig(const std::wstring& path)
{
    // Load data from the config file using std::ifstream

    std::ifstream configRaw(path);
    std::string configString((std::istreambuf_iterator<char>(configRaw)), std::istreambuf_iterator<char>());
    configRaw.close();
    return Config(configString);
}

void suspendMinecraftThread()
{
	NtSuspendThread(hMcThreadHandle, NULL);
}

std::wstring constructAmethystDLLPath()
{
	wchar_t buffer[MAX_PATH];
    // Get the localappdata path
    size_t pathLength = GetEnvironmentVariable(L"LOCALAPPDATA", buffer, MAX_PATH);
    std::wstring path(buffer, pathLength);
    path += L"\\Amethyst\\";
    std::wstring configPath = path + L"launcher_config.json";
    std::wcout << "Config Path: " << configPath << "\n";
    path += L"\\mods\\";
    Config config = loadConfig(configPath);
    std::cout << config.injectedMod << ": Runtime Version\n";
    // Config.injectedMod str to wstr
    std::wstring injectedMod(config.injectedMod.begin(), config.injectedMod.end());
    path += injectedMod;
    path += L"\\AmethystRuntime.dll";
    return path;
}

void InjectIntoMinecraft(std::wstring& path)
{
    LoadLibrary(path.c_str());
}

void proxy()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);
    std::cout << "Locating NtSuspendThread\n";
    NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtSuspendThread");
    std::cout << "NtSuspendThread located at " << NtSuspendThread << "\n";
    // Suspend the thread of the client so we can inject into it
    std::cout << "Suspending Minecraft thread\n";
    suspendMinecraftThread();
    std::cout << "Minecraft thread suspended\n";

    std::cout << "Locating Amethyst DLL\n";
    std::wstring path = constructAmethystDLLPath();
    std::wcout << "Amethyst DLL Path: " << path << "\n";
    std::cout << "Injecting Amethyst DLL\n";
    InjectIntoMinecraft(path);
    std::cout << "Amethyst DLL Injected\n";
    std::cout << "Locating AmethystInit\n";
    AmethystInit = (AmethystInitPtr)GetProcAddress(GetModuleHandle(L"AmethystRuntime.dll"), "Init");
    std::cout << "AmethystInit located at " << AmethystInit << "\n";
    std::cout << "Handing control to the Amethyst Runtime\n";
    AmethystInit(dMcThreadID, hMcThreadHandle);

}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hClientModule = GetModuleHandle(NULL);
        // Create a seperate thread to do the proxying after caching the currentThreadID
        dMcThreadID = GetCurrentThreadId();
        hMcThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, dMcThreadID);
        // Create a thread to do the proxying
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)proxy, NULL, NULL, NULL);
    default:
		break;
    }
    return TRUE;
}
