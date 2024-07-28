#pragma once
#include <string>
#include <minecraft/src/common/world/level/BlockSourceListener.hpp>
#include <minecraft/src/common/world/level/block/LevelEvent.hpp>

enum class ParticleType;
struct ResolvedItemIconInfo;
class HashedString;
class BlockPos;
class CompoundTag;
class MolangVariableMap;
struct ScreenshotOptions;

namespace cg { class ImageBuffer; }

class LevelListener : public BlockSourceListener {
public:
    ~LevelListener() = default;

    virtual void allChanged() {}
    
    virtual void sendServerLegacyParticle(ParticleType name, class Vec3 const& pos, class Vec3 const& dir, int data) {}
    
    virtual void addParticleEffect(const HashedString& effect, const Actor& actor, const HashedString& locator, const Vec3& emitterOffset, const MolangVariableMap& molangVariables) {}
    
    virtual void addTerrainParticleEffect(const BlockPos& pos, const Block& block, const Vec3& emitterPosition, float intensity, float velocityScalar, float emitterRadius) {}

    virtual void addTerrainSlideEffect(const BlockPos& pos, const Block& block, const Vec3& emitterPosition, float intensity, float velocityScalar, float emitterRadius) {}

    virtual void addBreakingItemParticleEffect(const Vec3& pos, ParticleType type, const ResolvedItemIconInfo&) {}

    virtual void playMusic(std::string const& name, class Vec3 const& pos, float songOffset, float volume) {}

    virtual void playStreamingMusic(std::string const& name, int x, int y, int z) {}

    virtual void onEntityAdded(class Actor& entity) {}

    virtual void onEntityRemoved(class Actor& entity) {}

    virtual void onChunkLoaded(class ChunkSource& source, class LevelChunk& lc) {}

    virtual void onChunkReloaded(class ChunkSource& source, class LevelChunk& lc) {}

    virtual void onSubChunkLoaded(class ChunkSource& source, class LevelChunk& lc, short, bool) {}

    virtual void onChunkUnloaded(class LevelChunk& lc) {}

    virtual void onLevelDestruction(const std::string& levelId) {}

    virtual void levelEvent(LevelEvent type, const Vec3& pos, int data) {}

    virtual void levelEvent(LevelEvent type, const CompoundTag& data) {}

    virtual void takePicture(cg::ImageBuffer& outImage, Actor* camera, Actor* target, ScreenshotOptions& screenshotOptions) {}

    virtual void playerListChanged() {}
};