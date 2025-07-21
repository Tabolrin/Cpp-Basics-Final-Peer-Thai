#include "Level.h"
#include "Ui.h"
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Map.h"
#include <iostream>

Level::Level(Levels mapLevel, Player& p)
{
	levelNum = mapLevel;
	player = p;
	map =  Map(levelNum);

	// Pick file based on level
	switch (levelNum)
	{
		case 1: 
			filePath = "Level1_Map.txt";
			break;
		case 2: 
			filePath = "Level2_Map.txt"; 
			break;
		case 3:
			filePath = "Level3_Map.txt";
			break;
	}

	LoadMapFile();
	map.Initialize(mapWidth, mapHeight);
	Ui::PrintFrame(*this, map.GetLevel(), player);
}

void Level::LoadMapFile()
{
	std::ifstream file(filePath);

	if (!file) return;

	std::string line;
	std::vector<std::string> lines;

	while (std::getline(file, line))
	{
		lines.push_back(line);

		if (line.length() < mapWidth)
			mapWidth = line.length();
	}

	mapHeight = lines.size();

	for (int x = 0; x < mapHeight; ++x) 
	{
		for (int y = 0; y < lines[x].length(); ++y) 
		{
			char ch = lines[x][y];
			Vector2 pos(x, y);
			if (ch == Map::ENEMY)
				PopulateEnemies(ch, pos);
		}

		for (int y = lines[x].length(); y < mapWidth; ++y)
		{
			PopulateEnemies(Map::CLEAR, Vector2(x, y));
		}
	}
}

void Level::PopulateEnemies(char ch, const Vector2& pos)
{
		//add new enemy with relevant coordinates
}

void Level::Update()
{
	UpdateEnemies();
}

bool Level::CheckWin() 
{
	//add if, or use function from player to check
	//if player is next to the exit tile, set playerAtExit to true
	return playerAtExit;
}

void Level::TransitionToNext()
{
	system("cls");
	std::cout<< "Transition to Level " << (levelNum + 1) << "!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}



void Level::UpdateEnemies()
{
	for (auto* e : enemies)
	{
		Vector2 dir(0, 1);
	}
}

Map& Level::GetMap() { return map; }

void Level::InitiateCombat(Player& p, Unit& e)
{
	Ui::AddToLog("Combat!");
}