#include "amethyst/Utility.hpp"
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include <shlobj_core.h>
#include "windows.h"

using namespace winrt;
using namespace Windows::Storage;

fs::path GetComMojangPath()
{
    StorageFolder localFolder = ApplicationData::Current().LocalFolder();
    fs::path localPath = localFolder.Path().c_str();
    return localPath / L"games" / L"com.mojang";
}

fs::path GetAmethystFolder()
{
    return GetComMojangPath() / L"amethyst";
}

std::string StringFromWstring(std::wstring wstring)
{
    return winrt::to_string(wstring);
}

std::wstring WstringFromString(std::string string)
{
    return winrt::to_hstring(string).data();
}
