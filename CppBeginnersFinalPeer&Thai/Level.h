#pragma once
#ifndef _LEVEL_
#define _LEVEL_

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Levels.h"
#include <vector>
#include <string>


class Level
{
private:
	Map* map;
	Player& player;
	Vector2 exitPos;
	bool playerAtExit = false;
	Levels levelNum;
	std::string filePath;
	size_t mapWidth = 0, mapHeight = 0;
	std::vector<Enemy*> enemies;
	std::vector<std::string> mapLines;


	void LoadMapFile();

public:

	Level(Levels mapLevel, Player& p);

	void Update();

	bool CheckWin();

	std::vector<Enemy*> GetEnemiesList() { return enemies; }

	void SetPlayerAtExit(bool val) { playerAtExit = val; }

	void TransitionToNext();

	Map& GetMap();

	void UpdateEnemies();

	void InitiateCombat(Player& p, Unit& e);
};
#endif