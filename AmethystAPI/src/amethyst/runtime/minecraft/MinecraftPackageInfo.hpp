#include "minecraft/src-deps/core/semVer/SemVersion.hpp"
#include <string>
#include <winrt/Windows.ApplicationModel.h>

namespace Amethyst {
    class MinecraftPackageInfo {
    public:
        std::string mName;
        std::string mFullname;
        std::string mFamilyName;
        std::string mPublisher;
        SemVersion mVersion;
        winrt::Windows::ApplicationModel::Package mPackage = winrt::Windows::ApplicationModel::Package(nullptr);

    public:
        MinecraftPackageInfo();
    };
}

