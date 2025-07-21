#include "Game.h"
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

Game::Game() {
	player = new Player(Vector2(0, 0));
	currentLevel = new Level(1, *player);
}

void Game::RunGameLoop() {
	auto lastTime = high_resolution_clock::now();
	float accumulator = 0.0f;
	const float dt = 0.1f;
	bool running = true;
	int currentLevelNum = 1;

	while (running) {
		auto now = high_resolution_clock::now();
		float delta = duration<float>(now - lastTime).count();
		lastTime = now;
		accumulator += delta;

		while (accumulator >= dt) {
			if (kbhit()) {
				char key = getch();
				Vector2 dir(0, 0);
				if (key == 'w') dir.x = -1;
				else if (key == 's') dir.x = 1;
				else if (key == 'a') dir.y = -1;
				else if (key == 'd') dir.y = 1;
				currentLevel->MovePlayer(dir);
			}

			currentLevel->UpdateEnemies();

			for (auto* e : currentLevel->enemies)
			{
				if (e->getPosition() == player->getPosition() + Vector2(1, 0)) 
				{
					currentLevel->InitiateCombat(*player, *e);
				}
			}

			currentLevel->Update();

			if (currentLevel->CheckWin()) {
				currentLevel->TransitionToNext();
				delete currentLevel;
				currentLevelNum++;
				if (currentLevelNum > 3) running = false;
				else currentLevel = new Level(currentLevelNum, *player);
			}

			accumulator -= dt;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	delete currentLevel;
	delete player;
}