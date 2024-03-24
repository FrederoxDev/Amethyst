#include "minecraft/src-deps/core/semVer/SemVersion.h"
#include <string>
#include <winrt/Windows.ApplicationModel.h>

namespace Amethyst {
    class MinecraftInfo {
    public:
        std::string mName;
        std::string mFullname;
        std::string mFamilyName;
        std::string mPublisher;
        SemVersion mVersion;
        winrt::Windows::ApplicationModel::Package mPackage = winrt::Windows::ApplicationModel::Package(nullptr);

    public:
        MinecraftInfo();
    };
}

