#pragma once
#include "minecraft/src-client/common/module/GameModuleClient.hpp"
#include <amethyst/Memory.hpp>

class Experiments;
class IResourcePackRepository;
class ResourcePackStack;
class BaseGameVersion;
struct PackIdVersion;

class VanillaGameModuleClient {
public:
    // 1.20.71.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E9 4C 89 8D ? ? ? ? 49 8B F0
    void initializeResourceStack(const Experiments*, IResourcePackRepository&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};