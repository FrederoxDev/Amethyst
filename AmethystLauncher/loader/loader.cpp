#include "loader.h"
#include <filesystem>
#include <tlhelp32.h>

// Function to get process handle by name
DWORD GetProcessIdByName(const wchar_t* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32First(snapshot, &processEntry)) {
            do {
                if (_wcsicmp(processEntry.szExeFile, processName) == 0) {
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

std::string modLoader::GetAmethystPath() 
{
    std::string baseAmethystPath = "";
	char* appdata = getenv("appdata");
	if (appdata == nullptr) {
        printf("Could not find amethyst path\n");
		std::abort();
	}
	baseAmethystPath = std::string(appdata) + "\\amethyst";
    if (!fs::exists(baseAmethystPath)) {
        // I would be using getenv but that is throwing an exception for some reason so no
		printf("Could not find amethyst path\n");
		std::abort();
	}
	
	return baseAmethystPath;
}

modLoader::modLoader() 
{
	// We do this so we dont have to call GetAmethystPath() constantly which is slow 
	amethystPath = GetAmethystPath();
	modsPath = amethystPath + "\\mods";
    getMinecraftWindowHandle();
}

// This code was yoinked from my mod loader SBL https://github.com/Duckos-Mods/SBL/blob/master/src/core/loader.cpp xD
void modLoader::getMinecraftWindowHandle()
{
    printf("Getting minecraft window handle\n");
    DWORD procID = GetProcessIdByName(L"Minecraft.Windows.exe");
    if (procID == 0)
    {
        printf("starting minecraft\n");
        system("explorer.exe shell:appsFolder\\Microsoft.MinecraftUWP_8wekyb3d8bbwe!App");
        while (procID == 0)
        {
            procID = GetProcessIdByName(L"Minecraft.Windows.exe");
        }
    }

    HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    _minecraftWindowHandle = procHandle;
}

void modLoader::InjectRuntime()
{
	// Get the path to the amethyst runtime dll
    std::string runtimePath = modsPath + "/AmethystRuntime/AmethystRuntime.dll"; // get the path to the runtime dll from the mods folder
    if (!fs::exists(runtimePath)) {
        printf("Could not find runtime dll at %s\n", runtimePath.c_str());
		std::abort();
	}

    printf("Injecting runtime dll from path %s\n", runtimePath.c_str());

    injectDLL(runtimePath);
}	

void modLoader::injectDLL(const std::string& path) 
{
    LPVOID dll = VirtualAllocEx(_minecraftWindowHandle, NULL, path.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (dll == NULL)
    {
		printf("Failed to allocate memory for dll\n");
		return;
	}
    if (!WriteProcessMemory(_minecraftWindowHandle, dll, path.c_str(), path.length() + 1, NULL))
    {
		printf("Failed to write dll to memory\n");
		return;
	}

	HANDLE thread = CreateRemoteThread(_minecraftWindowHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, dll, NULL, NULL);
    if (thread == NULL)
    {
		printf("Failed to create remote thread\n");
		return;
	}

	WaitForSingleObject(thread, INFINITE);
	VirtualFreeEx(_minecraftWindowHandle, dll, 0, MEM_RELEASE);
}