#pragma once
#ifndef _UI_
#define _UI_
#include "Level.h"
#include "Unit.h"
#include <queue>
#include <string>
#include "Player.h"
#include "Map.h"

class Ui
{
private:
	static std::queue<std::string> log;
	static const int MAX_LOG_SIZE = 6;


public:
	static void PrintFrame(Level& currentLevel, Levels level, Player& player);
	static void PrintOpeningAndTutorials();
	static void RequireEnterPressToProgress();

	static void InitialMapDraw(Map map);
};
#endif