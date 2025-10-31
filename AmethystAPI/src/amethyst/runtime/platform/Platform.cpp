#include "Platform.hpp"

bool Amethyst::Platform::IsDedicatedServer() const {
    return GetPlatformType() == PlatformType::WindowsServer;
}