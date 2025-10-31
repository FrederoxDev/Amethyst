#pragma once
#include "platforms/WindowsPlatformCommon.hpp"

class WindowsServerPlatform : public WindowsPlatformCommon {
public:
    WindowsServerPlatform(HANDLE mcThreadHandle);

    virtual Amethyst::PlatformType GetPlatformType() const override;
    virtual fs::path GetComMojangPath() const override;
    virtual fs::path GetAmethystFolder() const override;
	virtual std::string GetPlatformFolderName() override;

	virtual void ShutdownWaitForInput() override;

	virtual uintptr_t GetMinecraftBaseAddress() const override;
	virtual size_t GetMinecraftSize() const override;
};