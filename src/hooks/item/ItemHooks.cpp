#include "loader/AmethystRuntime.hpp"

#include "hooks/item/ItemHooks.hpp"

#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/AmethystContext.hpp>
#include <mc/src/common/world/item/ItemStack.hpp>
#include <mc/src/common/world/level/Level.hpp>

#include <memory>

bool ShowAdvancedItemInfo = false;

SafetyHookInline _Item_appendFormattedHovertext;
void Item_appendFormattedHovertext(const Item* self, const ItemStackBase& stack, Level& level, std::string& hovertext, bool showCategory)
{
    _Item_appendFormattedHovertext.thiscall<
        void,
        const Item*,
        const ItemStackBase&,
        Level&,
        std::string&,
        bool>(self, stack, level, hovertext, showCategory
    );

    std::string itemNamespace = self->mNamespace;
    std::string modName;
    std::weak_ptr<const Amethyst::Mod> mod;
    if (itemNamespace.empty() || itemNamespace == "minecraft")
    {
        modName = "Minecraft";
    }
    else if (!(mod = AmethystRuntime::getContext()->mModLoader->GetModByNamespace(itemNamespace)).expired()) {
        modName = mod.lock()->mInfo->FriendlyName;
    }
    else {
        modName.reserve(itemNamespace.size());
        bool cap = true;
        for (char c : itemNamespace) {
            if (c == '_') {
                modName.push_back(' ');
                cap = true;
            }
            else if (cap) {
                modName.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
                cap = false;
            }
            else {
                modName.push_back(c);
            }
        }
    }

    if (ShowAdvancedItemInfo) {
        hovertext += std::format("\n§8{}§r", self->mFullName.getString());

        if (stack.mAuxValue != 0 && stack.mAuxValue != 0x7fff)
            hovertext += std::format("\n§8Data: {}§r", stack.mAuxValue);

        auto block = self->getLegacyBlock();
        if (block && !block->mTags.empty()) {
            hovertext += "\n§8Block Tags:§r";
            for (const auto& tag : block->mTags) {
                hovertext += std::format("\n§8  #{}§r", tag.getString());
            }
        }

        if (!self->mTags.empty()) {
            hovertext += "\n§8Item Tags:§r";
            for (const auto& tag : self->mTags) {
                hovertext += std::format("\n§8  #{}§r", tag.getString());
            }
        }
        
        if (stack.mUserData)
            hovertext += std::format("\n§8NBT: {} tag(s)§r", stack.mUserData->mTags.size());
    }

    hovertext += std::format("\n§o§9{}§r", modName);
}

void CreateItemHooks()
{
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();
    VHOOK(Item, appendFormattedHovertext, this);
}