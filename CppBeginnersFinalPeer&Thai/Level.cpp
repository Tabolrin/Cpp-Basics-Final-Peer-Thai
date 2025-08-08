#include "Elements.h"
#include "Level.h"
#include "PatrolPoints.h"
#include "FileIO.h" 
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

    // ---- draw the map exactly as loaded ----
    for (int x = 0; x < mapHeight; ++x)
    {
        for (int y = 0; y < mapWidth; ++y)
        {
            pos = Vector2(static_cast<int>(x), static_cast<int>(y));
            char ch = mapLines[x][y];
            map->UpdatePosition(pos, ch, Ui::GetColorForChar(ch));
        }
    }

    // ---- place player and spawn enemies (with patrol points) ----
    int enemyIndex = 0; // track which enemy we’re on for this level

    for (int x = 0; x < mapHeight; ++x)
    {
        for (int y = 0; y < mapWidth; ++y)
        {
            pos = Vector2(static_cast<int>(x), static_cast<int>(y));
            char ch = map->GetCharAt(pos);

            if (ch == Symbols::PLAYER)
            {
                player.SetPosition(pos);
            }
            else if (ch == Symbols::ENEMY)
            {
                InfoGenerator infoGen;
                Enemy* temp = new Enemy(static_cast<int>(levelNum), pos);

                // Pick the patrol table for this level
                const Vector2(*patrols)[2] = nullptr;
                int patrolCount = 0;

                switch (levelNum)
                {
                    case Scenes::LEVEL_1:
                        patrols = LEVEL1_PATROLS; patrolCount = LEVEL1_PATROLS_COUNT; 
                        break;

                    case Scenes::LEVEL_2:
                        patrols = LEVEL2_PATROLS; patrolCount = LEVEL2_PATROLS_COUNT;
                        break;

                    case Scenes::LEVEL_3: patrols = LEVEL3_PATROLS;
                        patrolCount = LEVEL3_PATROLS_COUNT;
                        break;
                }
                
                if (patrols && enemyIndex < static_cast<size_t>(patrolCount))
                {
                    (*temp).AddPatrolPoint(*map, patrols[enemyIndex][0]);
                    (*temp).AddPatrolPoint(*map, patrols[enemyIndex][1]);
                }

                enemies.push_back(temp);
                ++enemyIndex;
            }
        }
    }

    Ui::PrintLevel(*this, levelNum, player, true);
}


void Level::LoadMapFile()
{
	auto lines = FileIO::LoadFileLines(filePath);

	if (lines.empty()) 
	{
		std::cout << "Error opening map file: " << filePath << std::endl;
		return;
	}

	mapLines = std::move(lines);

	//  Compute mapHeight as the number of lines
	mapHeight = static_cast<size_t>(mapLines.size());

	// Compute mapWidth as the longest line
	mapWidth = 0;
	for (const auto& line : mapLines)
	{
		if (line.size() > mapWidth) 
			mapWidth = line.size();
	}

	// Pad any shorter lines with 'CLEAR' symbol so all rows have equal length
	for (auto& line : mapLines)
	{
		if (line.size() < mapWidth)
			line.append(mapWidth - line.size(), static_cast<char>(Symbols::CLEAR));
	}
}

void Level::Update()
{
	if(!player.InCombat)
		UpdateEnemies();

    Ui::PrintLevel(*this, levelNum, player);
}

bool Level::CheckWin() 
{
	return player.IsAtExit;
}


void Level::UpdateEnemies()
{
	for (auto* enemy : enemies)
	{
		enemy->Update(*map, player);
	}
}

Map& Level::GetMap() { return *map; }

Level::~Level()
{
	for (Enemy* enemy : enemies)
		delete enemy; 

	delete map; 
}