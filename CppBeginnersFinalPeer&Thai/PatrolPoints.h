#pragma once
#include "Vector2.h"

//row=x, col=y
// Two points per enemy, in the same order LevelLoader finds 'M' (enemy) tiles 

// -------------------- LEVEL 1 --------------------
static const Vector2 LEVEL1_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(2,  10), Vector2(7, 10) },
    /* Enemy 1 */ { Vector2(14,  18), Vector2(12,  18) },
};
static const int LEVEL1_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL1_PATROLS) / sizeof(LEVEL1_PATROLS[0]));

// -------------------- LEVEL 2 --------------------
static const Vector2 LEVEL2_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(7,11), Vector2(4,20) },
    /* Enemy 1 */ { Vector2(2,28), Vector2(6,28) },
    /* Enemy 2 */ { Vector2(4,37), Vector2(7,45) },
    /* Enemy 3 */ { Vector2(7,18), Vector2(7,38) },
};
static const int LEVEL2_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL2_PATROLS) / sizeof(LEVEL2_PATROLS[0]));

// -------------------- LEVEL 3 --------------------
static const Vector2 LEVEL3_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(5,35), Vector2(8,26) },
    /* Enemy 1 */ { Vector2(4,9), Vector2(9,5) },
    /* Enemy 2 */ { Vector2(13,20), Vector2(13,15) },
    /* Enemy 3 */ { Vector2(15,32), Vector2(17,38) },
};
static const int LEVEL3_PATROLS_COUNT = static_cast<int>(sizeof(LEVEL3_PATROLS) / sizeof(LEVEL3_PATROLS[0]));
