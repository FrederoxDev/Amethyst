/// @symbols
#pragma once
#include "mc/src-deps/core/file/Path.hpp"
#include "mc/src-deps/core/resource/ResourceHelper.hpp"
#include <amethyst/Imports.hpp>

class IInPackagePacks {
public:
    struct MetaData {
    public:
        Core::PathBuffer<std::string> mPath;
        bool mIsHidden;
        PackCategory mPackCategory;

        MetaData(const Core::Path& path, const bool isHidden, PackCategory packCategory) {
            mPath.mContainer = path.mPathPart.mUtf8StdString;
            mIsHidden = isHidden;
            mPackCategory = packCategory;
        }
    };

    /// @vidx {0, this}
    MC virtual ~IInPackagePacks() = 0;
    /// @vidx {1, this}
    MC virtual std::vector<IInPackagePacks::MetaData> getPacks(PackType packType) const = 0;
};