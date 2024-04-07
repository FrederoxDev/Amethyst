#pragma once
#include <string>

/**
 * Returns the path to the amethyst UWP folder
 */
std::string GetAmethystFolder();

std::string StringFromWstring(std::wstring wstring);
std::wstring WstringFromString(std::string string);