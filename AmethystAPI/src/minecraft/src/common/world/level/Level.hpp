#pragma once

#include <memory>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <minecraft/src/common/world/level/ILevel.hpp>
#include <minecraft/src/common/world/level/BlockSourceListener.hpp>
#include <minecraft/src/common/world/level/IWorldRegistriesProvider.hpp>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>
#include <minecraft/src/common/world/level/dimension/DimensionFactory.hpp>

// client code included on server?
#include <minecraft/src-client/common/client/renderer/texture/BaseLightTextureImageBuilder.hpp>

class PacketSender;

class Level : public ILevel, public BlockSourceListener, public IWorldRegistriesProvider {
public:
    /* this + 40   */ std::byte padding40[800];
    /* this + 840  */ const ItemRegistryRef mItemRegistry;
    /* this + 856  */ std::byte padding856[2008];
    /* this + 2864 */ PacketSender* mPacketSender;
    /* this + 2872 */ std::byte padding2872[2648];
    /* this + 5520 */ bool isClientSide;
    /* this + 5521 */ std::byte padding5521[887];
    /* this + 6408 */ std::shared_ptr<OwnerPtr<DimensionFactory>> mDimensionFactory;     // its actually a gsl::not_null but compiler hates that despite the fact we don't construct level
    /* this + 6424 */ std::byte padding6424[6512 - 6424];
    /* this + 6512 */ Factory<BaseLightTextureImageBuilder, Level&, Scheduler&> mLightTextureImageBuilderFactory;
};

// 1.21.0.3
static_assert(offsetof(Level, mPacketSender) == 2864);
static_assert(offsetof(Level, isClientSide) == 5520);