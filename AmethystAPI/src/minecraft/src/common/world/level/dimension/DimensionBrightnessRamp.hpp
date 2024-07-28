#pragma once

class DimensionBrightnessRamp {
public:
    float mBrightnessRamp[16];

public:
    virtual ~DimensionBrightnessRamp() = default;
    void buildBrightnessRamp();
    float getBaseAmbientValue();

    DimensionBrightnessRamp();
};