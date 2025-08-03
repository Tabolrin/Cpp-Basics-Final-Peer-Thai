#include "Elements.h"
#include "Level.h"
#include "Scenes.h"
#include "Map.h"
#include "Symbols.h"
#include "InfoGenerator.h"
#include "Ui.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

Level::Level(Scenes mapLevel, Player& player) : levelNum(mapLevel), player(player)
{
    map = new Map(levelNum);

    // Pick file based on level
    switch (levelNum)
    {
        case Scenes::LEVEL_1:
            filePath = "Level1_Map.txt";
            break;
        case Scenes::LEVEL_2:
            filePath = "Level2_Map.txt"; 
            break;
        case Scenes::LEVEL_3:
            filePath = "Level3_Map.txt";
            break;
    }

    LoadMapFile();
    (*map).Initialize(mapWidth, mapHeight);

	Vector2 pos;

	for (size_t x = 0; x < mapHeight; ++x)
		for (size_t y = 0; y < mapWidth; ++y)
		{
			pos = Vector2(x, y);
			char ch = mapLines[x][y];
			map->UpdatePosition(pos, ch, Ui::GetColorForChar(ch));
		}
	

	for (size_t x = 0; x < mapHeight; ++x)
	{
		for (size_t y = 0; y < mapWidth; ++y)
		{
			pos = Vector2(x, y);
			char ch = map->GetCharAt(pos);

			if (ch == Symbols::PLAYER)
				player.SetPosition(pos);

			else if (ch == Symbols::ENEMY)
			{
				InfoGenerator infoGen;
				Enemy* temp = new Enemy(static_cast<int>(levelNum), pos);
				(*temp).AddPatrolPoint(*map, Vector2(2, 10));
				(*temp).AddPatrolPoint(*map, Vector2(7, 10));
				
				enemies.push_back(temp);
			}
		}
	}

	//Debug print
	//map->UpdatePosition(Vector2(2, 10), 'A', Ui::GetColorForChar('G'));
	//map->UpdatePosition(Vector2(7, 10), 'B', Ui::GetColorForChar('G'));
    Ui::PrintLevel(*this, levelNum, player);
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