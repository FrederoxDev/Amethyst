#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include <shlobj_core.h>
#include <filesystem>
#include <fstream>
#include <amethyst/Log.hpp>
#include "amethyst/Utility.hpp"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "windows.h"

using namespace winrt;
using namespace Windows::Storage;

std::string StringFromWstring(std::wstring wstring)
{
    return winrt::to_string(wstring);
}

std::wstring WstringFromString(std::string string)
{
    return winrt::to_hstring(string).data();
}

std::string ReadTextFile(const fs::path& filePath)
{
    std::ifstream file(filePath);
    Assert(file.is_open(), "Failed to open file '{}'", filePath.string());

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
