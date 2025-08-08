#pragma once
#include "Vector2.h"

//row=x, col=y
// Two points per enemy, in the same order LevelLoader finds 'M' (enemy) tiles 

// -------------------- LEVEL 1 --------------------
static const Vector2 LEVEL1_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(3,  11), Vector2(8, 11) },
    /* Enemy 1 */ { Vector2(15,  19), Vector2(13,  19) },
};
static const int LEVEL1_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL1_PATROLS) / sizeof(LEVEL1_PATROLS[0]));

// -------------------- LEVEL 2 --------------------
static const Vector2 LEVEL2_PATROLS[][2] = 
{
    /* Enemy 0 */ { Vector2(8,12), Vector2(5,21) },
    /* Enemy 1 */ { Vector2(3,29), Vector2(7,29) },
    /* Enemy 2 */ { Vector2(5,38), Vector2(8,46) },
    /* Enemy 3 */ { Vector2(8,19), Vector2(8,39) },
};
static const int LEVEL2_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL2_PATROLS) / sizeof(LEVEL2_PATROLS[0]));

// -------------------- LEVEL 3 --------------------
static const Vector2 LEVEL3_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(6,36), Vector2(9,27) },
    /* Enemy 1 */ { Vector2(5,8), Vector2(10,6) },
    /* Enemy 2 */ { Vector2(14,21), Vector2(14,16) },
    /* Enemy 3 */ { Vector2(16,33), Vector2(18,39) }, // ← the “oddball” can be vertical here
    // add/remove rows if enemy count changes
};

static const int LEVEL3_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL3_PATROLS) / sizeof(LEVEL3_PATROLS[0]));
