#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src/common/AppPlatformListener.hpp>

namespace mce {
    class RenderMaterialInfo;

    class RenderMaterialGroupBase {
    public:
        virtual ~RenderMaterialGroupBase();
        virtual mce::RenderMaterialInfo& getMaterialInfo(const HashedString& material);
        virtual void clearMaterial(const HashedString& material);
    };

    class RenderMaterialGroup : public AppPlatformListener, public mce::RenderMaterialGroupBase {
    public:
        static RenderMaterialGroup* common;
    };
};