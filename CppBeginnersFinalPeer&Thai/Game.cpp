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
    using Clock = std::chrono::high_resolution_clock;

    auto lastUpdateTime = Clock::now();          // wall-clock time at last frame
    float timeAccumulator = 0.0f;                  // how much un-processed time we’ve gathered
    constexpr float fixedTimeStep = 0.75f;          // ←– change this to alter tick rate (in seconds)
    bool  isRunning = true;
    Levels currentLevelId = Levels::MAP_LEVEL1;

    while (isRunning)
    {
        // 1) Measure elapsed time since last frame
        auto   currentTime = Clock::now();
        float  frameTime = std::chrono::duration<float>(currentTime - lastUpdateTime).count();
        lastUpdateTime = currentTime;
        timeAccumulator += frameTime;

        // 2) Immediate player input/action every frame
        player->Update(currentLevel->GetMap(), *player);

        // 3) Fixed-timestep world update: runs when we've accumulated ≥ fixedTimeStep
        while (timeAccumulator >= fixedTimeStep)
        {
            currentLevel->Update();            // your existing map/AI/physics tick
            timeAccumulator -= fixedTimeStep;  // consume that slice of time
        }

        // 4) Check win/level-flow here...
        if (currentLevel->CheckWin())
        {
            /* …transition… */ 
        }

        // 5) Tiny sleep so CPU isn’t pegged at 100%
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Cleanup…
    delete currentLevel;
    delete player;
}


