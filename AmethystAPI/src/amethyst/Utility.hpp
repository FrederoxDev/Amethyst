#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

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