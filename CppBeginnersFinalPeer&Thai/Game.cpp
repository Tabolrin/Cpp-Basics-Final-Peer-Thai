#include "Game.h"
#include "Level.h"
#include "Scenes.h"
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
	currentLevel = new Level(Scenes::LEVEL_1, *player);
}

void Game::RunGameLoop()
{
    using Clock = std::chrono::high_resolution_clock;

    auto lastUpdateTime = Clock::now();          // wall-clock time at last frame
    float timeAccumulator = 0.0f;                  // how much un-processed time we’ve gathered
    constexpr float fixedTimeStep = 0.75f;          // ←– change this to alter tick rate (in seconds)
    bool  isRunning = true;
    Scenes currentLevelId = Scenes::LEVEL_1;

    while (isRunning)
    {
        auto   currentTime = Clock::now();
        float  frameTime = std::chrono::duration<float>(currentTime - lastUpdateTime).count();
        lastUpdateTime = currentTime;
        timeAccumulator += frameTime;

        player->Update(currentLevel->GetMap(), *player);

        while (timeAccumulator >= fixedTimeStep)
        {
            currentLevel->Update();            // your existing map/AI/physics tick
            timeAccumulator -= fixedTimeStep;  // consume that slice of time
        }

        if (currentLevel->CheckWin())
        {
            /* …transition… */ 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Cleanup…
    delete currentLevel;
    delete player;
}


