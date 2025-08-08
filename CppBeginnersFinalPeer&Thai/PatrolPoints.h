#pragma once
#include "Vector2.h"

//row=x, col=y
// Two points per enemy, in the same order your Level loader finds 'M' tiles (row-major).

// -------------------- LEVEL 1 --------------------
static const Vector2 LEVEL1_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2( 0,  0), Vector2( 0, 0) },
    /* Enemy 1 */ { Vector2(0,  0), Vector2( 0,  0) },
};
static const int LEVEL1_PATROLS_COUNT =
static_cast<int>(sizeof(LEVEL1_PATROLS) / sizeof(LEVEL1_PATROLS[0]));

// -------------------- LEVEL 2 --------------------
static const Vector2 LEVEL2_PATROLS[][2] = 
{
    /* Enemy 0 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 1 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 2 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 3 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 4 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 5 */ { Vector2(0,0), Vector2(0,0) },
};
static const int LEVEL2_PATROLS_COUNT =
static_cast<int>(sizeof(LEVEL2_PATROLS) / sizeof(LEVEL2_PATROLS[0]));

// -------------------- LEVEL 3 --------------------
static const Vector2 LEVEL3_PATROLS[][2] =
{
    /* Enemy 0 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 1 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 2 */ { Vector2(0,0), Vector2(0,0) },
    /* Enemy 3 */ { Vector2(0,0), Vector2(0,0) }, // ← the “oddball” can be vertical here
    // add/remove rows if enemy count changes
};

static const int LEVEL3_PATROLS_COUNT =
static_cast<int>(sizeof(LEVEL3_PATROLS) / sizeof(LEVEL3_PATROLS[0]));
