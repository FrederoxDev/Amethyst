#include "minecraft/src-deps/core/semVer/SemVersion.h"
#include <string>
#include <winrt/Windows.ApplicationModel.h>

namespace Amethyst {
    class MinecraftInfo {
    public:
        std::string name;
        std::string fullname;
        std::string familyName;
        std::string publisher;
        SemVersion version;
        winrt::Windows::ApplicationModel::Package package = winrt::Windows::ApplicationModel::Package(nullptr);

    public:
        MinecraftInfo();
    };
}

