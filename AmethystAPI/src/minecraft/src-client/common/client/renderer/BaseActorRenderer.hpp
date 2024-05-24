#pragma once
#include <minecraft/src-client/common/client/renderer/ActorShaderManager.hpp>

class BaseActorRenderer : public ActorShaderManager {
public:
    /* this + 56  */ mce::MaterialPtr mNameTagMat;
    /* this + 72  */ mce::MaterialPtr mDepthTestedNameTagMat;
    /* this + 88  */ mce::MaterialPtr mDepthTestedNameTextMat;
    /* this + 104 */ mce::MaterialPtr mDepthTestedHealthMat;

    virtual ~BaseActorRenderer() override;
    BaseActorRenderer();
};