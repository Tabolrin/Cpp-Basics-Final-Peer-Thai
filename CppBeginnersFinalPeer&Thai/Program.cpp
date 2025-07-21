#include <iostream>
#include "Game.h"
//DEBUG
#include "Map.h"
#include "Levels.h"
#include "Level.h"
#include "Ui.h"
#include "Player.h"

int main()
{
	//Game game;
	//game.RunGameLoop();
	Player player(Vector2{ 0, 0 });
	Level level(Levels::MAP_LEVEL1, player);
	Ui::InitialMapDraw(level.GetMap());
	return 0;
}