#include "MinecraftPackageInfo.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Utility.hpp"

Amethyst::MinecraftPackageInfo::MinecraftPackageInfo()
{
    // Get the current uwp package
    auto package = winrt::Windows::ApplicationModel::Package::Current();

    // Read the data
    std::string name = StringFromWstring(package.Id().Name().data());
    std::string fullname = StringFromWstring(package.Id().FullName().data());
    std::string familyName = StringFromWstring(package.Id().FamilyName().data());
    std::string publisher = StringFromWstring(package.Id().Publisher().data());

    // Build version
    SemVersion version = {
        package.Id().Version().Major,
        package.Id().Version().Minor,
        package.Id().Version().Build,
        fmt::format(
            "{}",
            package.Id().Version().Revision
            ),
        "",
        fmt::format(
            "{}.{}.{}.{}",
            package.Id().Version().Major,
            package.Id().Version().Minor,
            package.Id().Version().Build,
            package.Id().Version().Revision
            ),
        true,
        false
    };

    // Fill info
    this->mName = name;
    this->mFullname = name;
    this->mFamilyName = familyName;
    this->mPublisher = publisher;
    this->mVersion = version;
    this->mPackage = package;
}