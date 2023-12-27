#pragma once
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <tlhelp32.h>
#include "amethyst/Config.h"
#include <fstream>
#include <sstream>

void ReportIssue(LPCWSTR message);
#define WIN32_LEAN_AND_MEAN

class ModLoader {
public:
	ModLoader(Config);
	void InjectRuntime();

private:
	void getMinecraftWindowHandle();
	void InjectDLL(const std::string& dllPath);

private:
	Config mConfig;
	std::string mAmethystPath;
	std::string mModsPath;
	HANDLE mMinecraftWindowHandle;
};
std::string GetAmethystPath();
std::string GetAmethystUWPFolder();