#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ItemRegistry;
class BlockDefinitionGroup;
class ResourcePackManager;
class Experiments;

class RegisterItemsEvent : public BaseEvent {
public:
    ItemRegistry& itemRegistry;

    RegisterItemsEvent(ItemRegistry& registry) 
        : itemRegistry(registry) {}
};

class RegisterBlocksEvent : public BaseEvent {
public:
    BlockDefinitionGroup& blockDefinitions;

    RegisterBlocksEvent(BlockDefinitionGroup& blockDefs) 
        : blockDefinitions(blockDefs) {}
};

class InitBlockGraphics : public BaseEvent {
public:
    ResourcePackManager& resources;
    const Experiments& experiments;

    InitBlockGraphics(ResourcePackManager& resources, const Experiments& experiments)
        : resources(resources), experiments(experiments) {}
};