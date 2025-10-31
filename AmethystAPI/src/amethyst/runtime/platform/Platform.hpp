#pragma once
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;

namespace Amethyst {
enum class PlatformType : uint8_t {
	WindowsClient, 
	WindowsServer
};

class Platform {
public:
	virtual ~Platform() = default;
	virtual PlatformType GetPlatformType() const = 0;

	virtual fs::path GetComMojangPath() const = 0;
	virtual fs::path GetAmethystFolder() const = 0;
	virtual std::string GetPlatformFolderName() = 0;

    virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
    virtual void ShutdownWaitForInput() = 0;

	virtual bool HasRequestedStop() const = 0;
    virtual bool HasRequestedHotReload() const = 0;

	virtual void AttachDebugger() const = 0;
    virtual void InitializeConsole() const = 0;
	virtual void PauseGameThread() const = 0;
    virtual void ResumeGameThread() const = 0;

	virtual uintptr_t GetMinecraftBaseAddress() const = 0;
	virtual size_t GetMinecraftSize() const = 0;

	bool IsDedicatedServer() const;
};

} // namespace Amethyst