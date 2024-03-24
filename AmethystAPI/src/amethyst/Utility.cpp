#include "amethyst/Utility.h"
#include <codecvt>
#include <locale>

// std::wstring_convert<std::codecvt_utf8<wchar_t>> is deprecated
// but there is no replacement for it currently (as of C++23)
// TODO find a working replacement
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstring);
}

std::wstring WstringFromString(std::string string)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(string);
}
