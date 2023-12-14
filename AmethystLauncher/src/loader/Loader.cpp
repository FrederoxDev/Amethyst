#include "Loader.h"

void ModLoader::ReportIssue(LPCWSTR message) {
    MessageBoxW(NULL, message, L"AmethystLauncher", MB_ICONERROR | MB_OK);
}

// Function to get process handle by name
DWORD GetProcessIdByName(const wchar_t* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32First(snapshot, &processEntry)) {
            do {
                wchar_t wideProcessName[MAX_PATH];
                MultiByteToWideChar(CP_ACP, 0, processEntry.szExeFile, -1, wideProcessName, MAX_PATH);

                if (_wcsicmp(wideProcessName, processName) == 0) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
    }

    return processId;
}

namespace fs = std::filesystem;

std::string ModLoader::GetAmethystPath() 
{
    std::string baseAmethystPath = "";

	char* appdata = getenv("appdata");
	if (appdata == nullptr) {
        ReportIssue(L"Failed to get %appdata%");
		std::abort();
	}

	baseAmethystPath = std::string(appdata) + "/Amethyst";
    if (!fs::exists(baseAmethystPath)) {
        fs::create_directories(baseAmethystPath);
	}
	
	return baseAmethystPath;
}

ModLoader::ModLoader() 
{
	// We do this so we dont have to call GetAmethystPath() constantly which is slow 
	mAmethystPath = GetAmethystPath();
	mModsPath = mAmethystPath + "/mods";
    getMinecraftWindowHandle();
}

// This code was yoinked from my mod loader SBL https://github.com/Duckos-Mods/SBL/blob/master/src/core/loader.cpp xD
void ModLoader::getMinecraftWindowHandle()
{
    DWORD procID = GetProcessIdByName(L"Minecraft.Windows.exe");
    if (procID == 0)
    {
        system("explorer.exe shell:appsFolder\\Microsoft.MinecraftUWP_8wekyb3d8bbwe!App");

        while (procID == 0)
        {
            procID = GetProcessIdByName(L"Minecraft.Windows.exe");
        }
    }

    HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    mMinecraftWindowHandle = procHandle;
}

void ModLoader::InjectRuntime()
{
	// Get the path to the amethyst runtime dll
    std::string runtimePath = mModsPath + "/AmethystRuntime/AmethystRuntime.dll"; // get the path to the runtime dll from the mods folder
    if (!fs::exists(runtimePath)) {
        ReportIssue(L"Failed to find AmethystRuntime.dll");
		std::abort();
	}

    injectDLL(runtimePath);
}	

void ModLoader::injectDLL(const std::string& path) 
{
    LPVOID dll = VirtualAllocEx(mMinecraftWindowHandle, NULL, path.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (dll == NULL)
    {
        ReportIssue(L"Failed to allocate memory for AmethystRuntime.dll");
		return;
	}
    if (!WriteProcessMemory(mMinecraftWindowHandle, dll, path.c_str(), path.length() + 1, NULL))
    {
        ReportIssue(L"Failed to write AmethystRuntime.dll to memory");
		return;
	}

	HANDLE thread = CreateRemoteThread(mMinecraftWindowHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, dll, NULL, NULL);
    if (thread == NULL)
    {
        ReportIssue(L"Failed to create remote thread");
		return;
	}

	WaitForSingleObject(thread, INFINITE);
	VirtualFreeEx(mMinecraftWindowHandle, dll, 0, MEM_RELEASE);
}