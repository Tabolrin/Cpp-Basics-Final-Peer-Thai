#include "Game.h"
#include "Level.h"
#include "Levels.h"
#include "Map.h"
#include "Player.h"
#include "Ui.h"
#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>

using namespace std::chrono;

Game::Game() 
{
	player = new Player(Vector2(0, 0));
	currentLevel = new Level(Levels::MAP_LEVEL1, *player);
}

void Game::RunGameLoop()
{
	auto lastTime = high_resolution_clock::now();
	float accumulator = 0.0f;
	const float dt = 0.1f;
	bool running = true;
	Levels currentLevelNum = Levels::MAP_LEVEL1;

	while (running) 
	{
		auto now = high_resolution_clock::now();
		float delta = duration<float>(now - lastTime).count();

		lastTime = now;
		accumulator += delta;

		player->Update(currentLevel->GetMap(), *player);

		//currentLevel->UpdateEnemies();

		/*for (auto* e : currentLevel->GetEnemiesList())
		{
			if (e->getPosition() == player->getPosition() + Vector2(1, 0)) 
			{
				currentLevel->InitiateCombat(*player, *e);
			}
		}*/

		currentLevel->Update();

		if (currentLevel->CheckWin()) 
		{
			currentLevel->TransitionToNext();
			delete currentLevel;

			int intCurLvl = static_cast<int>(currentLevelNum);
			intCurLvl += 1;
			currentLevelNum = static_cast<Levels>(intCurLvl);

			if (currentLevelNum > 3) running = false;
			else currentLevel = new Level(currentLevelNum, *player);
		}

		accumulator -= dt;
	}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		delete currentLevel;
		delete player;
}

