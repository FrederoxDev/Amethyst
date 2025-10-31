#include "loader/AmethystRuntime.hpp"
#include "hooks/item/ItemHooks.hpp"
#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/ModContext.hpp>

#include <mc/src/common/world/item/ItemStack.hpp>
#include <mc/src/common/world/level/Level.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/locale/I18n.hpp>

#include <memory>

bool ShowAdvancedItemInfo = false;

#ifdef CLIENT
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
    else if (!(mod = Amethyst::GetContext().mModLoader->GetModByNamespace(itemNamespace)).expired()) {
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
        std::string itemDataLocalized = "text.amethyst.item_data"_i18n;
        std::string blockTagsLocalized = "text.amethyst.block_tags"_i18n;
        std::string itemTagsLocalized = "text.amethyst.item_tags"_i18n;
        std::string nbtCountLocalized = "text.amethyst.nbt_count"_i18n;

        hovertext += std::format("\n§8{}§r", self->mFullName.getString());

        if (stack.mAuxValue != 0 && stack.mAuxValue != 0x7fff)
            hovertext += "\n" + std::vformat(itemDataLocalized, std::make_format_args(stack.mAuxValue));

        auto block = self->getLegacyBlock();
        if (block && !block->mTags.empty()) {
            hovertext += "\n" + blockTagsLocalized;
            for (const auto& tag : block->mTags) {
                hovertext += std::format("\n§8  #{}§r", tag.getString());
            }
        }

        if (!self->mTags.empty()) {
            hovertext += "\n" + itemTagsLocalized;
            for (const auto& tag : self->mTags) {
                hovertext += std::format("\n§8  #{}§r", tag.getString());
            }
        }
        
        if (stack.mUserData) {
            size_t nbtCount = stack.mUserData->mTags.size();
            hovertext += "\n" + std::vformat(nbtCountLocalized, std::make_format_args(nbtCount));
        }
    }
    else {
        std::string holdTextLocalized = "action.amethyst.show_advanced_item_info"_i18n;

        auto& options = *Amethyst::GetClientCtx().mOptions;
        auto& mapping = *options.getCurrentKeyboardRemapping();
        auto* keymapping = mapping.getKeymappingByAction("key.amethyst.show_advanced_item_info");
        std::string keyName = keymapping ? mapping.getMappedKeyName(*keymapping) : "Unknown";

        if (keymapping && keymapping->isAssigned())
            hovertext += "\n" + std::vformat(holdTextLocalized, std::make_format_args(keyName));
    }

    hovertext += std::format("\n§o§9{}§r", modName);
}
#endif

void CreateItemHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();

	#ifdef CLIENT
    VHOOK(Item, appendFormattedHovertext, this);
	#endif
}