#include "Mod.h"

Mod::Mod(std::string modName)
{
    this->modName = modName;
    fs::path dllPath = GetTempDll();

    // Loads the mod in a temporary directory so that the original DLL can still be built to
    hModule = LoadLibrary(dllPath.string().c_str());
    if (hModule == NULL) {
        DWORD error = GetLastError();

        switch (error) {
        case 0x5:
            Log::Error("[AmethystRuntime] '{}' does not have the required privileges!", dllPath.string());
            throw std::exception();
        case 0x7e:
            Log::Error("[AmethystRuntime] Failed to find '{}'", dllPath.string());
            throw std::exception();
        default:
            Log::Error("[AmethystRuntime] Failed to load '{}.dll', error code: 0x{:x}", modName, error);
            throw std::exception();
        }
    }

    return;
}

FARPROC Mod::GetFunction(const char* funcName)
{
    return GetProcAddress(hModule, funcName);
}

void Mod::Free()
{
    FreeLibrary(hModule);
}

fs::path Mod::GetTempDll()
{
    std::string modShortened = modName;
    size_t atPos = modShortened.find("@");

    if (atPos != std::string::npos) {
        modShortened = modShortened.substr(0, atPos);
    }

    // Ensure temp directory exists
    fs::path tempDir = GetAmethystUWPFolder() + "temp/" + modName + "/";
    if (!fs::exists(tempDir)) fs::create_directories(tempDir);

    fs::path originalDll = GetAmethystUWPFolder() + "mods/" + modName + "/" + modShortened + ".dll";
    if (!fs::exists(originalDll)) {
        Log::Error("[AmethystRuntime] Could not find '{}.dll'", modShortened);
        throw std::exception();
    }

    fs::path tempDll = tempDir.string() + modShortened + ".dll";

    try {
        fs::copy_file(originalDll, tempDll, fs::copy_options::overwrite_existing);
    }
    catch (const std::filesystem::filesystem_error& e) {
        Log::Error("[AmethystRuntime] {} (Error code: {})", e.what(), e.code().value());
        throw std::exception();
    }

    return tempDll;
}