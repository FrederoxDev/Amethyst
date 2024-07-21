#pragma once
#include <memory>

class Dimension;
class BlockPos;
class BaseLightData;
struct BrightnessPair;

class ClientInstance;
using IClientInstance = ClientInstance;

class BaseLightTextureImageBuilder {
public:
    const Dimension* mDimension;

public:
    virtual ~BaseLightTextureImageBuilder();
    virtual void init(Dimension&);
    virtual bool hasBrightnessModifier();
    virtual void getModifiedBlockBrightnessColor(const BlockPos&, BrightnessPair&);
    virtual std::unique_ptr<BaseLightData> createBaseLightTextureData(IClientInstance&, const BaseLightData&);
};

namespace LightTextureImageBuilderFactory {
    // 1.21.0.3 - 0x3FE9B30 (Non-unique signature)
    static void registerLightImageBuilders(Factory<BaseLightTextureImageBuilder, Level&, Scheduler&>& factory);
}