#pragma once
#include <iostream>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

class modLoader
{
private:
	// Get the path to the amethyst folder
	std::string GetAmethystPath();
	void getMinecraftWindowHandle();
	void injectDLL(const std::string& dllPath);
private:
	// The path to the amethyst folder
	std::string amethystPath;
	// The path to the amethyst mods folder
	std::string modsPath;

	HANDLE _minecraftWindowHandle;

public:
	modLoader();

	void InjectRuntime();
};

