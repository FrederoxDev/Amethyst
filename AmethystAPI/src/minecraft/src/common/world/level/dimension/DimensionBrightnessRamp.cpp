#include "DimensionBrightnessRamp.hpp"
#include <minecraft/src/common/CommonTypes.hpp>
#include <algorithm>

DimensionBrightnessRamp::DimensionBrightnessRamp() {
    for (int i = 0; i < 16; i++) {
        mBrightnessRamp[i] = 0.0f;
    }
} 

void DimensionBrightnessRamp::buildBrightnessRamp()
{
    float baseAmbient = getBaseAmbientValue();
    float inverseMax = 1.0f / Brightness::MAX.value;

    for (int i = 0; i < 16; i++) {
        float value = ((i * inverseMax) / (((1.0f - (i * inverseMax)) * 3.0f) + 1.0f)) + baseAmbient;
        mBrightnessRamp[i] = std::clamp(value, 0.0f, 1.0f);
    }
}

float DimensionBrightnessRamp::getBaseAmbientValue()
{
    return 0.0f;
}
