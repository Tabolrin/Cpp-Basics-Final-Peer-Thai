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
	static COORD notificationLineIndex;
	static int lastNotificationLength;
	static void MapDraw(Map& map);

public:
	static void PrintLevel(Level& LevelObj, Scenes level, Player& player);
	static void Tutorials();
	static void RequireEnterPressToProgress();
	static const WORD GetColorForChar(char ch) ;
	static void PrintOpeningScreen();
	static void PrintCombatVisual(Elements enemyElement);
	static void PrintWinScreen();
	static void PrintLoseScreen();
	static void PrintLevelTransition();
	static void PrintNotification(const Items Item);
	static void PrintNotification(const std::string message);
	static void PrintPlayerPartyInfo(Player& player);
};
