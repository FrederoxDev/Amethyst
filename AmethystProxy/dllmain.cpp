#pragma once


#pragma comment(linker, "/export:ApplyCompatResolutionQuirking=c:\\windows\\system32\\dxgi.ApplyCompatResolutionQuirking,@1")
#pragma comment(linker, "/export:CompatString=c:\\windows\\system32\\dxgi.CompatString,@2")
#pragma comment(linker, "/export:CompatValue=c:\\windows\\system32\\dxgi.CompatValue,@3")
#pragma comment(linker, "/export:CreateDXGIFactory=c:\\windows\\system32\\dxgi.CreateDXGIFactory,@10")
#pragma comment(linker, "/export:CreateDXGIFactory1=c:\\windows\\system32\\dxgi.CreateDXGIFactory1,@11")
#pragma comment(linker, "/export:CreateDXGIFactory2=c:\\windows\\system32\\dxgi.CreateDXGIFactory2,@12")
#pragma comment(linker, "/export:DXGID3D10CreateDevice=c:\\windows\\system32\\dxgi.DXGID3D10CreateDevice,@13")
#pragma comment(linker, "/export:DXGID3D10CreateLayeredDevice=c:\\windows\\system32\\dxgi.DXGID3D10CreateLayeredDevice,@14")
#pragma comment(linker, "/export:DXGID3D10GetLayeredDeviceSize=c:\\windows\\system32\\dxgi.DXGID3D10GetLayeredDeviceSize,@15")
#pragma comment(linker, "/export:DXGID3D10RegisterLayers=c:\\windows\\system32\\dxgi.DXGID3D10RegisterLayers,@16")
#pragma comment(linker, "/export:DXGIDeclareAdapterRemovalSupport=c:\\windows\\system32\\dxgi.DXGIDeclareAdapterRemovalSupport,@17")
#pragma comment(linker, "/export:DXGIDumpJournal=c:\\windows\\system32\\dxgi.DXGIDumpJournal,@4")
#pragma comment(linker, "/export:DXGIGetDebugInterface1=c:\\windows\\system32\\dxgi.DXGIGetDebugInterface1,@18")
#pragma comment(linker, "/export:DXGIReportAdapterConfiguration=c:\\windows\\system32\\dxgi.DXGIReportAdapterConfiguration,@19")
#pragma comment(linker, "/export:PIXBeginCapture=c:\\windows\\system32\\dxgi.PIXBeginCapture,@5")
#pragma comment(linker, "/export:PIXEndCapture=c:\\windows\\system32\\dxgi.PIXEndCapture,@6")
#pragma comment(linker, "/export:PIXGetCaptureState=c:\\windows\\system32\\dxgi.PIXGetCaptureState,@7")
#pragma comment(linker, "/export:SetAppCompatStringPointer=c:\\windows\\system32\\dxgi.SetAppCompatStringPointer,@8")
#pragma comment(linker, "/export:UpdateHMDEmulationStatus=c:\\windows\\system32\\dxgi.UpdateHMDEmulationStatus,@9")

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
HMODULE hProxied = LoadLibrary(L"C:\\Windows\\System32\\dxgi.dll");
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
