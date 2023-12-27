#include "Loader.h"
#include <codecvt>
namespace fs = std::filesystem;

void ReportIssue(LPCWSTR message) {
    MessageBoxW(NULL, message, L"AmethystLauncher", MB_ICONERROR | MB_OK);
}

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

std::string GetAmethystUWPFolder() {
    char* path;
    size_t path_length;
    errno_t err = _dupenv_s(&path, &path_length, "LocalAppData");

    if (err) {
        ReportIssue(L"_dupenv_s failed to find %LocalAppData%");
        throw std::exception();
    }

    if (path == 0) {
        ReportIssue(L"%LocalAppData% was 0");
        throw std::exception();
    }

    std::string app_data(path);
    free(path);

    std::string amethyst_folder = app_data + "/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/";
    return amethyst_folder;
}

ModLoader::ModLoader(Config config) : mConfig(config)
{
    mAmethystPath = GetAmethystPath();
    mModsPath = mAmethystPath + "/mods";
}

std::string GetAmethystPath() 
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
    std::string mod_shortened = mConfig.injectedMod;
    size_t atPos = mod_shortened.find("@");

    if (atPos != std::string::npos) {
        mod_shortened = mod_shortened.substr(0, atPos);
    }

    if (!fs::exists(mModsPath)) {
        Log::Info("Creating mods directory: {}\n", mModsPath);
        fs::create_directories(mModsPath);
	}
    
    std::string runtimePath = fmt::format("{}/{}/{}.dll", mModsPath, mConfig.injectedMod, mod_shortened);
    Log::Info("Runtime: {}\n", runtimePath);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    if (!fs::exists(runtimePath)) {
        std::string message = fmt::format("Failed to find AmethystRuntime.dll. Make sure to install the Amethyst Runtime into {}", mModsPath);
        ReportIssue(converter.from_bytes(message).c_str());
		std::abort();
	}

    getMinecraftWindowHandle();

    InjectDLL(runtimePath);
}	

void ModLoader::InjectDLL(const std::string& path) 
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