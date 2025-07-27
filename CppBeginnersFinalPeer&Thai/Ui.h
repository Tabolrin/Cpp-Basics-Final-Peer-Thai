#pragma once

#include "Level.h"
#include "Levels.h"
#include "Unit.h"
#include <queue>
#include <string>
#include "Player.h"
#include "Map.h"

class Ui
{
private:
	static const int MAX_LOG_SIZE = 6;

public:
	static void PrintFrame(Level& LevelObj, Levels level, Player& player);
	static void PrintOpeningAndTutorials();
	static void RequireEnterPressToProgress();
	static void MapDraw(Map map);
	static const WORD GetColorForChar(char ch) ;
};
