#pragma once

#include "common/client/renderer/ImageInfo.h"

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