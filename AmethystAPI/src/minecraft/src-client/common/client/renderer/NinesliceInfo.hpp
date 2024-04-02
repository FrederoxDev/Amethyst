#pragma once
#include "minecraft/src-client/common/client/renderer/ImageInfo.hpp"

struct NinesliceInfo {
public:
    ImageInfo mTopLeft;
    ImageInfo mTopRight;
    ImageInfo mBottomLeft;
    ImageInfo mBottomRight;
    glm::tvec2<float> mUVScale;
    std::vector<ImageInfo> mLeft;
    std::vector<ImageInfo> mTop;
    std::vector<ImageInfo> mRight;
    std::vector<ImageInfo> mBottom;
    std::vector<ImageInfo> mMiddle;
};