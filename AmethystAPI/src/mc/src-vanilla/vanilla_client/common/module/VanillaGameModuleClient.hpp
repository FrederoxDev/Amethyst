/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src-client/common/module/GameModuleClient.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "gsl/gsl"

class Experiments;
class IResourcePackRepository;
class ResourcePackStack;
class BaseGameVersion;
class ResourcePackRepository;

class VanillaGameModuleClient {
public:
    MC static uintptr_t $vtable_for_this;

    /// @vidx { 0, this }
    MC virtual ~VanillaGameModuleClient();

    virtual void unk_1();
    virtual void unk_2();
    virtual void unk_3();

    /// @vidx { 4, this }
    MC virtual void initializeResourceStack(const Experiments&, const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};