#pragma once
#include <cstdint>

namespace mce {
class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(unsigned int color)
    {
        this->r = (float)((color & 0xFF000000) >> 24) / 255.0f;
        this->g = (float)((color & 0x00FF0000) >> 16) / 255.0f;
        this->b = (float)((color & 0x0000FF00) >> 8) / 255.0f;
        this->a = (float)((color & 0x000000FF)) / 255.0f;
    }

    Color()
    {
        this->r = 0.0f;
        this->g = 0.0f;
        this->b = 0.0f;
        this->a = 0.0f;
    }

    uint32_t As32() const
    {
        struct PackedColors {
            union {
                struct {
                    char r;
                    char g;
                    char b;
                    char a;
                };
                unsigned int intValue;
            };
        };

        PackedColors result{};
        result.r = static_cast<char>(this->r * 255.0f);
        result.g = static_cast<char>(this->g * 255.0f);
        result.b = static_cast<char>(this->b * 255.0f);
        result.a = static_cast<char>(this->a * 255.0f);

        return result.intValue;
    }

    static const Color WHITE;
    static const Color BLACK;

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;

    static const Color TRANS;

    /// Vanilla color code: §0 (Foreground)
    static const Color FONT_BLACK;

    /// Vanilla color code: §1 (Foreground)
    static const Color FONT_DARK_BLUE;

    /// Vanilla color code: §2 (Foreground)
    static const Color FONT_DARK_GREEN;

    /// Vanilla color code: §3 (Foreground)
    static const Color FONT_DARK_AQUA;

    /// Vanilla color code: §4 (Foreground)
    static const Color FONT_DARK_RED;

    /// Vanilla color code: §5 (Foreground)
    static const Color FONT_DARK_PURPLE;

    /// Vanilla color code: §6 (Foreground)
    static const Color FONT_GOLD;

    /// Vanilla color code: §7 (Foreground)
    static const Color FONT_GRAY;

    /// Vanilla color code: §8 (Foreground)
    static const Color FONT_DARK_GRAY;

    /// Vanilla color code: §9 (Foreground)
    static const Color FONT_BLUE;

    /// Vanilla color code: §a (Foreground)
    static const Color FONT_GREEN;

    /// Vanilla color code: §b (Foreground)
    static const Color FONT_AQUA;

    /// Vanilla color code: §c (Foreground)
    static const Color FONT_RED;

    /// Vanilla color code: §d (Foreground)
    static const Color FONT_LIGHT_PURPLE;

    /// Vanilla color code: §e (Foreground)
    static const Color FONT_YELLOW;

    /// Vanilla color code: §f (Foreground)
    static const Color FONT_WHITE;

    /// Vanilla color code: §g (Foreground)
    static const Color FONT_MINECOIN_GOLD;

    /// Vanilla color code: §h (Foreground)
    static const Color FONT_MATERIAL_QUARTZ;

    /// Vanilla color code: §i (Foreground)
    static const Color FONT_MATERIAL_IRON;

    /// Vanilla color code: §j (Foreground)
    static const Color FONT_MATERIAL_NETHERITE;

    /// Vanilla color code: §m (Foreground)
    static const Color FONT_MATERIAL_REDSTONE;

    /// Vanilla color code: §n (Foreground)
    static const Color FONT_MATERIAL_COPPER;

    /// Vanilla color code: §p (Foreground)
    static const Color FONT_MATERIAL_GOLD;

    /// Vanilla color code: §q (Foreground)
    static const Color FONT_MATERIAL_EMERALD;

    /// Vanilla color code: §s (Foreground)
    static const Color FONT_MATERIAL_DIAMOND;

    /// Vanilla color code: §t (Foreground)
    static const Color FONT_MATERIAL_LAPIS;

    /// Vanilla color code: §u (Foreground)
    static const Color FONT_MATERIAL_AMETHYST;

    /// Vanilla color code: §0 (Background)
    static const Color FONT_BLACK_BG;

    /// Vanilla color code: §1 (Background)
    static const Color FONT_DARK_BLUE_BG;

    /// Vanilla color code: §2 (Background)
    static const Color FONT_DARK_GREEN_BG;

    /// Vanilla color code: §3 (Background)
    static const Color FONT_DARK_AQUA_BG;

    /// Vanilla color code: §4 (Background)
    static const Color FONT_DARK_RED_BG;

    /// Vanilla color code: §5 (Background)
    static const Color FONT_DARK_PURPLE_BG;

    /// Vanilla color code: §6 (Background)
    static const Color FONT_GOLD_BG;

    /// Vanilla color code: §7 (Background)
    static const Color FONT_GRAY_BG;

    /// Vanilla color code: §8 (Background)
    static const Color FONT_DARK_GRAY_BG;

    /// Vanilla color code: §9 (Background)
    static const Color FONT_BLUE_BG;

    /// Vanilla color code: §a (Background)
    static const Color FONT_GREEN_BG;

    /// Vanilla color code: §b (Background)
    static const Color FONT_AQUA_BG;

    /// Vanilla color code: §c (Background)
    static const Color FONT_RED_BG;

    /// Vanilla color code: §d (Background)
    static const Color FONT_LIGHT_PURPLE_BG;

    /// Vanilla color code: §e (Background)
    static const Color FONT_YELLOW_BG;

    /// Vanilla color code: §f (Background)
    static const Color FONT_WHITE_BG;

    /// Vanilla color code: §g (Background)
    static const Color FONT_MINECOIN_GOLD_BG;

    /// Vanilla color code: §h (Background)
    static const Color FONT_MATERIAL_QUARTZ_BG;

    /// Vanilla color code: §i (Background)
    static const Color FONT_MATERIAL_IRON_BG;

    /// Vanilla color code: §j (Background)
    static const Color FONT_MATERIAL_NETHERITE_BG;

    /// Vanilla color code: §m (Background)
    static const Color FONT_MATERIAL_REDSTONE_BG;

    /// Vanilla color code: §n (Background)
    static const Color FONT_MATERIAL_COPPER_BG;

    /// Vanilla color code: §p (Background)
    static const Color FONT_MATERIAL_GOLD_BG;

    /// Vanilla color code: §q (Background)
    static const Color FONT_MATERIAL_EMERALD_BG;

    /// Vanilla color code: §s (Background)
    static const Color FONT_MATERIAL_DIAMOND_BG;

    /// Vanilla color code: §t (Background)
    static const Color FONT_MATERIAL_LAPIS_BG;

    /// Vanilla color code: §u (Background)
    static const Color FONT_MATERIAL_AMETHYST_BG;
};
}; // namespace mce
