#pragma once

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

    /// Vanilla color code: §0 (Foreground)
    static const Color BLACK;

    /// Vanilla color code: §1 (Foreground)
    static const Color DARK_BLUE;

    /// Vanilla color code: §2 (Foreground)
    static const Color DARK_GREEN;

    /// Vanilla color code: §3 (Foreground)
    static const Color DARK_AQUA;

    /// Vanilla color code: §4 (Foreground)
    static const Color DARK_RED;

    /// Vanilla color code: §5 (Foreground)
    static const Color DARK_PURPLE;

    /// Vanilla color code: §6 (Foreground)
    static const Color GOLD;

    /// Vanilla color code: §7 (Foreground)
    static const Color GRAY;

    /// Vanilla color code: §8 (Foreground)
    static const Color DARK_GRAY;

    /// Vanilla color code: §9 (Foreground)
    static const Color BLUE;

    /// Vanilla color code: §a (Foreground)
    static const Color GREEN;

    /// Vanilla color code: §b (Foreground)
    static const Color AQUA;

    /// Vanilla color code: §c (Foreground)
    static const Color RED;

    /// Vanilla color code: §d (Foreground)
    static const Color LIGHT_PURPLE;

    /// Vanilla color code: §e (Foreground)
    static const Color YELLOW;

    /// Vanilla color code: §f (Foreground)
    static const Color WHITE;

    /// Vanilla color code: §g (Foreground)
    static const Color MINECOIN_GOLD;

    /// Vanilla color code: §h (Foreground)
    static const Color MATERIAL_QUARTZ;

    /// Vanilla color code: §i (Foreground)
    static const Color MATERIAL_IRON;

    /// Vanilla color code: §j (Foreground)
    static const Color MATERIAL_NETHERITE;

    /// Vanilla color code: §m (Foreground)
    static const Color MATERIAL_REDSTONE;

    /// Vanilla color code: §n (Foreground)
    static const Color MATERIAL_COPPER;

    /// Vanilla color code: §p (Foreground)
    static const Color MATERIAL_GOLD;

    /// Vanilla color code: §q (Foreground)
    static const Color MATERIAL_EMERALD;

    /// Vanilla color code: §s (Foreground)
    static const Color MATERIAL_DIAMOND;

    /// Vanilla color code: §t (Foreground)
    static const Color MATERIAL_LAPIS;

    /// Vanilla color code: §u (Foreground)
    static const Color MATERIAL_AMETHYST;


    /// Vanilla color code: §0 (Background)
    static const Color BLACK_BG;

    /// Vanilla color code: §1 (Background)
    static const Color DARK_BLUE_BG;

    /// Vanilla color code: §2 (Background)
    static const Color DARK_GREEN_BG;

    /// Vanilla color code: §3 (Background)
    static const Color DARK_AQUA_BG;

    /// Vanilla color code: §4 (Background)
    static const Color DARK_RED_BG;

    /// Vanilla color code: §5 (Background)
    static const Color DARK_PURPLE_BG;

    /// Vanilla color code: §6 (Background)
    static const Color GOLD_BG;

    /// Vanilla color code: §7 (Background)
    static const Color GRAY_BG;

    /// Vanilla color code: §8 (Background)
    static const Color DARK_GRAY_BG;

    /// Vanilla color code: §9 (Background)
    static const Color BLUE_BG;

    /// Vanilla color code: §a (Background)
    static const Color GREEN_BG;

    /// Vanilla color code: §b (Background)
    static const Color AQUA_BG;

    /// Vanilla color code: §c (Background)
    static const Color RED_BG;

    /// Vanilla color code: §d (Background)
    static const Color LIGHT_PURPLE_BG;

    /// Vanilla color code: §e (Background)
    static const Color YELLOW_BG;

    /// Vanilla color code: §f (Background)
    static const Color WHITE_BG;

    /// Vanilla color code: §g (Background)
    static const Color MINECOIN_GOLD_BG;

    /// Vanilla color code: §h (Background)
    static const Color MATERIAL_QUARTZ_BG;

    /// Vanilla color code: §i (Background)
    static const Color MATERIAL_IRON_BG;

    /// Vanilla color code: §j (Background)
    static const Color MATERIAL_NETHERITE_BG;

    /// Vanilla color code: §m (Background)
    static const Color MATERIAL_REDSTONE_BG;

    /// Vanilla color code: §n (Background)
    static const Color MATERIAL_COPPER_BG;

    /// Vanilla color code: §p (Background)
    static const Color MATERIAL_GOLD_BG;

    /// Vanilla color code: §q (Background)
    static const Color MATERIAL_EMERALD_BG;

    /// Vanilla color code: §s (Background)
    static const Color MATERIAL_DIAMOND_BG;

    /// Vanilla color code: §t (Background)
    static const Color MATERIAL_LAPIS_BG;

    /// Vanilla color code: §u (Background)
    static const Color MATERIAL_AMETHYST_BG;
};
}; // namespace mce
