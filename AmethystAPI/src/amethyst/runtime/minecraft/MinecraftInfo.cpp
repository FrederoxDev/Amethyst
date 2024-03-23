#include "MinecraftInfo.h"
#include "amethyst/Utility.h"

Amethyst::MinecraftInfo Amethyst::MinecraftInfo::getMinecraftInfo()
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
        std::format(
            "%i",
            package.Id().Version().Revision
            ),
        "",
        std::format(
            "%i.%i.%i.%i",
            package.Id().Version().Major,
            package.Id().Version().Minor,
            package.Id().Version().Build,
            package.Id().Version().Revision
            ),
        true,
        false
    };

    // Build info
    Amethyst::MinecraftInfo info = {
        name,
        fullname,
        familyName,
        publisher,
        version,
        package
    };

    return info;
}