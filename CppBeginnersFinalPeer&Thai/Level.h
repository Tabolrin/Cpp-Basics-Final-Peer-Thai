#pragma once
#include "Map.h"
#include "MapData.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Chest.h"
#include "Key.h"
#include "Exit.h"
#include <vector>
#include <string>

class Level {
private:
	Map map;
	MapData data;
	Player& player;
	std::vector<Enemy*> enemies;
	Vector2 keyLocation;
	bool playerAtExit = false;
	int levelNum;
	std::string filePath;
	int mapWidth = 0, mapHeight = 0;

	void LoadMapFile();
	void PopulateObjects(char ch, const Vector2& pos);

public:
	Level(int num, Player& p);

	void Update();

	bool CheckWin();

	void SetPlayerAtExit(bool val) { playerAtExit = val; }

	void TransitionToNext();

	Map& GetMap() { return map; }

	MapData& GetData() { return data; }

	void MovePlayer(const Vector2& dir);

	void UpdateEnemies();

	void InitiateCombat(Unit& p, Unit& e);
};