#include "amethyst/Utility.hpp"
#include <winrt/base.h>

std::string GetAmethystFolder()
{
    static std::string amethystFolder;

    if (amethystFolder.empty()) {
        char* path;
        size_t path_length;
        errno_t err = _dupenv_s(&path, &path_length, "LocalAppData");

        if (err) throw std::exception("Failed to get environment variable %LocalAppData%");
        if (path == nullptr) throw std::exception("%LocalAppData% was null");

        std::string localAppDataFolder(path);
        free(path);

        amethystFolder = localAppDataFolder + "/Amethyst/";
    }

    return amethystFolder;
}

std::string StringFromWstring(std::wstring wstring)
{
    return winrt::to_string(wstring);
}

std::wstring WstringFromString(std::string string)
{
    return winrt::to_hstring(string).data();
}
