/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-client/common/module/GameModuleClient.hpp"
#include "mc/src/common/resources/ResourcePackRepository.hpp"
#include "gsl/gsl"

class Experiments;
class IResourcePackRepository;
class ResourcePackStack;
class BaseGameVersion;

/// @vptr { 0x2BD1248, this, win-server }
/// @vptr { 0x4EC7070, this }
class VanillaGameModuleServer {
public:
    MC static uintptr_t $vtable_for_this;

    /// @vidx { 0, this }
    MC virtual ~VanillaGameModuleServer();

    virtual void unk_1();

    /// @vidx { 2, this }
    MC virtual void initializeBehaviorStack(const Experiments&, const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};