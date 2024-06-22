#pragma once
#include <string>
#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include <shlobj_core.h>
#include "windows.h"

namespace fs = std::filesystem;
using namespace winrt;
using namespace Windows::Storage;

/*
Returns a path to Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang
*/
fs::path GetComMojangPath();

/*
Returns a path to com.mojang/amethyst
*/
fs::path GetAmethystFolder();


std::string StringFromWstring(std::wstring wstring);
std::wstring WstringFromString(std::string string);