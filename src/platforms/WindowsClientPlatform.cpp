#include "WindowsClientPlatform.hpp"
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "windows.h"
#include <Psapi.h>

using namespace winrt;
using namespace Windows::Storage;

WindowsClientPlatform::WindowsClientPlatform(HANDLE mcThreadHandle)
    : WindowsPlatformCommon(mcThreadHandle) {}

Amethyst::PlatformType WindowsClientPlatform::GetPlatformType() const
{
    return Amethyst::PlatformType::WindowsClient;
}

fs::path WindowsClientPlatform::GetComMojangPath() const
{
    char appdata[MAX_PATH];
    GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH);
    return fs::path(appdata) / "Minecraft Bedrock" / "games" / "com.mojang";
}

fs::path WindowsClientPlatform::GetAmethystFolder() const
{
    return GetComMojangPath() / "amethyst";
}

std::string WindowsClientPlatform::GetPlatformFolderName() {
	return "win-client";
}

uintptr_t WindowsClientPlatform::GetMinecraftBaseAddress() const {
	return reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
}

size_t WindowsClientPlatform::GetMinecraftSize() const {
	HMODULE base = GetModuleHandleA("Minecraft.Windows.exe");
	if (base == nullptr) return 0;

	MODULEINFO moduleInfo;
	if (!GetModuleInformation(GetCurrentProcess(), base, &moduleInfo, sizeof(MODULEINFO))) return 0;

	return moduleInfo.SizeOfImage;
}
