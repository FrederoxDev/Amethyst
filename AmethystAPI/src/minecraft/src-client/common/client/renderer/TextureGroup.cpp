#include <minecraft/src-client/common/client/renderer/TextureGroup.hpp>
#include <minecraft/src-deps/coregraphics/ImageBuffer.hpp>

BedrockTexture& mce::TextureGroup::uploadTexture(const ResourceLocation& resource, const mce::TextureContainer& texture, std::optional<std::string_view> debugName)
{
    using function = BedrockTexture&(mce::TextureGroup::*)(const ResourceLocation&, const mce::TextureContainer&, std::optional<std::string_view>);

    struct multiInheritance {
        uintptr_t ptr;
        int displacement;
    };

    static auto func = std::bit_cast<function>(multiInheritance{
        //SigScan("40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 4D 8B F8 4C 8B F2 48 8B F1"),
        SlideAddress(0x08C96C0),
        0
    });

    return (this->*func)(resource, texture, debugName);
}

BedrockTexture& mce::TextureGroup::uploadTexture(const ResourceLocation& resource, cg::ImageBuffer imageBuffer)
{
    using function = BedrockTexture& (mce::TextureGroup::*)(const ResourceLocation&, cg::ImageBuffer);

    struct multiInheritance {
        uintptr_t ptr;
        int displacement;
    };

    static auto func = std::bit_cast<function>(multiInheritance{
        SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B F8 4C 8B EA 4C 8B E1"),
        0
    });

    return (this->*func)(resource, imageBuffer);
}