#include "WindowsServerPlatform.hpp"
#include <Psapi.h>

WindowsServerPlatform::WindowsServerPlatform(HANDLE mcThreadHandle) 
	: WindowsPlatformCommon(mcThreadHandle) {}

Amethyst::PlatformType WindowsServerPlatform::GetPlatformType() const {
    return Amethyst::PlatformType::WindowsServer;
}

fs::path WindowsServerPlatform::GetComMojangPath() const {
    return fs::current_path();
}

fs::path WindowsServerPlatform::GetAmethystFolder() const {
    return fs::current_path() / "amethyst";
}

std::string WindowsServerPlatform::GetPlatformFolderName() {
	return "win-server";
}

void WindowsServerPlatform::ShutdownWaitForInput() {
	Shutdown();
}

uintptr_t WindowsServerPlatform::GetMinecraftBaseAddress() const
{
    return reinterpret_cast<uintptr_t>(GetModuleHandleA("bedrock_server.exe"));
}

size_t WindowsServerPlatform::GetMinecraftSize() const
{
	HMODULE base = GetModuleHandleA("bedrock_server.exe");
	if (base == nullptr) return 0;

	MODULEINFO moduleInfo;
	if (!GetModuleInformation(GetCurrentProcess(), base, &moduleInfo, sizeof(MODULEINFO))) return 0;

	return moduleInfo.SizeOfImage;
}
