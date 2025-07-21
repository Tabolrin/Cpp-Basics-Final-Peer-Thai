#pragma once
#ifndef _ANIMALS_
#define _ANIMALS_

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <string>



class Level
{
private:
	Map map;
	Player& player;
	Vector2 exitPos;
	bool playerAtExit = false;
	Levels levelNum;
	std::string filePath;
	int mapWidth = 0, mapHeight = 0;
	std::vector<Enemy*> enemies;

	void LoadMapFile();
	void PopulateEnemies(char ch, const Vector2& pos);

public:


	Level(Levels mapLevel, Player& p);

	void Update();

	bool CheckWin();

	void SetPlayerAtExit(bool val) { playerAtExit = val; }

	void TransitionToNext();

	Map& GetMap();

	void UpdateEnemies();

	void InitiateCombat(Player& p, Unit& e);
};
#endif