#include "minecraft/src-deps/core/semVer/SemVersion.h"
#include <string>
#include <winrt/Windows.ApplicationModel.h>

namespace Amethyst {
    struct MinecraftInfo {
    public:
        std::string name;
        std::string fullname;
        std::string familyName;
        std::string publisher;
        SemVersion version;
        winrt::Windows::ApplicationModel::Package package;

    public:
        static MinecraftInfo getMinecraftInfo();
    };
}

