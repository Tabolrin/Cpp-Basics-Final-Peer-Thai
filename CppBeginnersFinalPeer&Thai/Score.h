#pragma once

struct Score 
{
    static int& Ref() { static int v = 0; return v; }
    static void Add(int scoreToAdd) { Ref() += scoreToAdd; }
    static int  Get() { return Ref(); }
    static void Reset() { Ref() = 0; }
};


namespace ScoreValues 
{
    constexpr int ENEMY_DEFEATED_BASE = 50;
    constexpr int ENEMY_LEVEL_BONUS = 10;   // × enemy level
    constexpr int CHEST_OPENED = 20;
    constexpr int KEY_PICKED = 25;
    constexpr int LEVEL_EXIT = 100;
}