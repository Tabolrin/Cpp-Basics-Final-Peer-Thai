#pragma once

enum class Colors : int
{
    // Foreground colors
    BLACK = 0, // Black
    DARK_BLUE = 1, // Dark Blue
    DARK_GREEN = 2, // Dark Green
    DARK_CYAN = 3, // Dark Cyan (Aqua)
    DARK_RED = 4, // Dark Red
    MAGENTA = 5, // Dark Magenta (Purple)
    DARK_YELLOW = 6, // Dark Yellow (Brown)
    LIGHT_GRAY = 7, // Light Gray (White)
    GRAY = 8, // Gray (Dark Gray)
    LIGHT_BLUE = 9, // Light Blue
    LIGHT_GREEN = 10, // Light Green
    LIGHT_CYAN = 11, // Light Cyan (Bright Aqua)
    LIGHT_RED = 12, // Light Red
    LIGHT_MAGENTA = 13, // Light Magenta (Bright Purple)
    LIGHT_YELLOW = 14, // Light Yellow
    BRIGHT_WHITE = 15, // Bright White

    // Background colors (shifted into the high 4 bits)
    BKG_BLACK = 0 << 4, // Background Black
    BKG_DARK_BLUE = 1 << 4, // Background Dark Blue
    BKG_DARK_GREEN = 2 << 4, // Background Dark Green
    BKG_DARK_CYAN = 3 << 4, // Background Dark Cyan (Aqua)
    BKG_DARK_RED = 4 << 4, // Background Dark Red
    BKG_MAGENTA = 5 << 4, // Background Dark Magenta (Purple)
    BKG_DARK_YELLOW = 6 << 4, // Background Dark Yellow (Brown)
    BKG_LIGHT_GRAY = 7 << 4, // Background Light Gray (White)
    BKG_GRAY = 8 << 4, // Background Gray (Dark Gray)
    BKG_LIGHT_BLUE = 9 << 4, // Background Light Blue
    BKG_LIGHT_GREEN = 10 << 4, // Background Light Green
    BKG_LIGHT_CYAN = 11 << 4, // Background Light Cyan (Bright Aqua)
    BKG_LIGHT_RED = 12 << 4, // Background Light Red
    BKG_LIGHT_MAGENTA = 13 << 4, // Background Light Magenta (Bright Purple)
    BKG_LIGHT_YELLOW = 14 << 4, // Background Light Yellow
    BKG_BRIGHT_WHITE = 15 << 4, // Background Bright White
};



