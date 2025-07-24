#include "Game.h"
#include "Player.h"
#include "Levels.h"
#include "Level.h"
#include "Ui.h"
#include "Map.h"
#include <conio.h>
#include <iostream>
#include <chrono>
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
	const float dt = 0.75f;
	bool running = true;
	Levels currentLevelNum = Levels::MAP_LEVEL1;

	while (running)
	{
		auto now = high_resolution_clock::now();
		float delta = duration<float>(now - lastTime).count();

		player->Update(currentLevel->GetMap(), *player);

		if (delta >= dt)
		{
			lastTime = now;

			currentLevel->Update(); // enemies update here

			if (currentLevel->CheckWin())
			{
				currentLevel->TransitionToNext();
				delete currentLevel;

				int intCurLvl = static_cast<int>(currentLevelNum);
				intCurLvl += 1;
				currentLevelNum = static_cast<Levels>(intCurLvl);

				if (currentLevelNum > 3)
					running = false;
				else
					currentLevel = new Level(currentLevelNum, *player);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // avoids CPU overuse
	}
}