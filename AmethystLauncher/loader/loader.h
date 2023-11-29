#pragma once
#include <iostream>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

class ModLoader {
public:
	ModLoader();
	void InjectRuntime();

private:
	std::string GetAmethystPath();
	void getMinecraftWindowHandle();
	void injectDLL(const std::string& dllPath);

private:
	std::string mAmethystPath;
	std::string mModsPath;
	HANDLE mMinecraftWindowHandle;
};

