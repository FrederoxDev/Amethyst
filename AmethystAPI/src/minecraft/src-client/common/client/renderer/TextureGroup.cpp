#include <minecraft/src-client/common/client/renderer/TextureGroup.hpp>

BedrockTexture& mce::TextureGroup::uploadTexture(const ResourceLocation& resource, const mce::TextureContainer& texture, std::optional<std::string_view> debugName)
{
    using function = decltype(&mce::TextureGroup::uploadTexture);

    struct multiInheritance {
        uintptr_t ptr;
        int displacement;
    };

    static auto func = std::bit_cast<function>(multiInheritance{
        SigScan("40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 4D 8B F8 4C 8B F2 48 8B F1"),
        0
    });

    return (this->*func)(resource, texture, debugName);

    //union {
    //    uintptr_t asPtr;
    //    function asFunc;
    //} cast;

    //cast.asPtr = SigScan("40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 4D 8B F8 4C 8B F2 48 8B F1");
    //return (this->*cast.asFunc)(resource, texture, debugName);
}
