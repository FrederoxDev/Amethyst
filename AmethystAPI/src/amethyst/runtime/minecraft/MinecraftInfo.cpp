#include "MinecraftInfo.h"
#include "amethyst/Log.h"
#include "amethyst/Utility.h"

Amethyst::MinecraftInfo::MinecraftInfo()
{
    // Get the current uwp package
    auto w_package = winrt::Windows::ApplicationModel::Package::Current();

    // Read the data
    std::string w_name = StringFromWstring(w_package.Id().Name().data());
    std::string w_fullname = StringFromWstring(w_package.Id().FullName().data());
    std::string w_familyName = StringFromWstring(w_package.Id().FamilyName().data());
    std::string w_publisher = StringFromWstring(w_package.Id().Publisher().data());

    // Build version
    SemVersion w_version = {
        w_package.Id().Version().Major,
        w_package.Id().Version().Minor,
        w_package.Id().Version().Build,
        std::format(
            "%i",
            w_package.Id().Version().Revision
            ),
        "",
        std::format(
            "%i.%i.%i.%i",
            w_package.Id().Version().Major,
            w_package.Id().Version().Minor,
            w_package.Id().Version().Build,
            w_package.Id().Version().Revision
            ),
        true,
        false
    };

    // Fill info
    this->name = w_name;
    this->fullname = w_name;
    this->familyName = w_familyName;
    this->publisher = w_publisher;
    this->version = w_version;
    this->package = w_package;
}