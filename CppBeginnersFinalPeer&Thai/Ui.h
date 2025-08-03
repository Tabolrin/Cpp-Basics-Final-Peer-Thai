#pragma once

#include "Level.h"
#include "Scenes.h"
#include "Unit.h"
#include <queue>
#include <string>
#include "Player.h"
#include "Map.h"

class Ui
{
private:
	static const int NOTIFICATION_LINE_INDEX = 6;
	static void MapDraw(Map map);
	static HANDLE hConsole ;


public:
	static void PrintLevel(Level& LevelObj, Scenes level, Player& player);
	static void Tutorials();
	static void RequireEnterPressToProgress();
	static const WORD GetColorForChar(char ch) ;
	static void PrintOpeningScreen();
	static void PrintCombatVisual ();
	static void PrintWinScreen();
	static void PrintLoseScreen();
	static void PrintLevelTransition();
	static void PrintNotification(const Items Item);
};
