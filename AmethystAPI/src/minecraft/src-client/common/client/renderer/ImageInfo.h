#pragma once
#include "glm/glm.hpp"

struct ImageInfo {
public:
    glm::tvec2<float> mPosition;
    glm::tvec2<float> mSize;
    glm::tvec2<float> mUV;
    glm::tvec2<float> mUVSize;
};