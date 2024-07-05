#pragma once
#include <minecraft/src-client/common/client/renderer/BaseActorRenderer.hpp>
#include <minecraft/src-client/common/client/renderer/BaseActorRenderContext.hpp>
#include <minecraft/src/common/world/phys/Vec3.hpp>

struct BlockActorRenderData;
class NameTagRenderObject;
class Tessellator;
class BlockActor;
class BlockSource;
class Block;

class BlockActorRenderer : public BaseActorRenderer {
public:
    virtual ~BlockActorRenderer() override;
    virtual mce::Color _getOverlayColor(Actor&, float) const override;
    virtual void render(BaseActorRenderContext&, BlockActorRenderData&) = 0;
    virtual void renderAlpha(BaseActorRenderContext&, BlockActorRenderData&) { return; };
    virtual std::vector<NameTagRenderObject> extractText(Tessellator&, BlockActor&, const std::string&, std::vector<int>&, Vec3, bool);

    BlockActorRenderer() : BaseActorRenderer() {};
};

struct BlockActorRenderData {
    /* this + 0  */ BlockSource& renderSource;
    /* this + 8  */ BlockActor& entity;
    /* this + 16 */ const Block& block;
    /* this + 24 */ const Vec3& position;
};