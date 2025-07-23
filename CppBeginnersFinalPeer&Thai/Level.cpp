#include "Level.h"
#include "Levels.h"
#include "Ui.h"
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Map.h"
#include <iostream>
#include "Symbols.h"

Level::Level(Levels mapLevel, Player& player) : levelNum(mapLevel), player(player)
{
    map = new Map(levelNum);

    // Pick file based on level
    switch (levelNum)
    {
        case Levels::MAP_LEVEL1: 
            filePath = "Level1_Map.txt";
            break;
        case Levels::MAP_LEVEL2:
            filePath = "Level2_Map.txt"; 
            break;
        case Levels::MAP_LEVEL3:
            filePath = "Level3_Map.txt";
            break;
    }

    LoadMapFile();
    (*map).Initialize(mapWidth, mapHeight);

	for (size_t x = 0; x < mapHeight; ++x)
	{
		for (size_t y = 0; y < mapWidth; ++y)
		{
			char ch = mapLines[x][y];

			if (ch == Symbols::PLAYER)
				player.setPosition(Vector2(x, y));

			map->UpdatePosition(Vector2(x, y), ch, Ui::GetColorForChar(ch));
		}
	}

    Ui::PrintFrame(*this, levelNum, player);
}

void Level::LoadMapFile()
{
	std::ifstream file(filePath);

	if (!file)
	{
		std::cout << "Error opening map file: " << filePath << std::endl;
		return;
	}

	std::string line;
	mapLines.clear();

	while (std::getline(file, line))
	{
		mapLines.push_back(line);
		mapWidth = line.length();
	}

	mapHeight = mapLines.size();

	/*for (int x = 0; x < mapHeight; ++x)
	{
		for (int y = 0; y < lines[x].length(); ++y) 
		{

		}
	}*/
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

Map& Level::GetMap() { return *map; }

void Level::InitiateCombat(Player& p, Unit& e)
{
	
}