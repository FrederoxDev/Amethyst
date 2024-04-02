#pragma once
#include "minecraft/src-deps/core/file/Path.hpp"
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"

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

    virtual ~IInPackagePacks();
    virtual std::vector<IInPackagePacks::MetaData> getPacks(PackType packType) const;
};