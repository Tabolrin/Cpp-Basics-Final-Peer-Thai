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
#include "Elements.h"

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


			/*
			else if (ch == Symbols::ENEMY)
			{
				Enemy temp = Enemy(10, 5, 5, Elements::FIRE, Vector2(x, y));
				temp.AddPatrolPoint(*map, Vector2(2, 11));
				
				temp.AddPatrolPoint(*map, Vector2(7, 11));
				
				enemies.push_back(&temp);
			}
			*/

			map->UpdatePosition(Vector2(x, y), ch, Ui::GetColorForChar(ch));

		}
	}
	Enemy temp = Enemy(10, 5, 5, Elements::FIRE, Vector2(5, 10));
	temp.AddPatrolPoint(*map, Vector2(2, 11));
	temp.AddPatrolPoint(*map, Vector2(7, 11));
	enemies.push_back(&temp);
	//Debug print
	//map->UpdatePosition(Vector2(2, 11), 'G', Ui::GetColorForChar('G'));
	//map->UpdatePosition(Vector2(7, 11), '8', Ui::GetColorForChar('G'));
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
		e->Update(*map, player);
	}
}

Map& Level::GetMap() { return *map; }

void Level::InitiateCombat(Player& p, Unit& e)
{
	
}