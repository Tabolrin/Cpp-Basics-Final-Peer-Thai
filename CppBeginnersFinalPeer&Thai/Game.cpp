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
    currentLevel = nullptr;
	currentScene = Scenes::OPENING; // Start with the opening scene
    MoveToScene(currentScene);
}

void Game::RunGameLoop()
{
    using Clock = std::chrono::high_resolution_clock;

    auto lastUpdateTime = Clock::now();          // wall-clock time at last frame
    float timeAccumulator = 0.0f;                  // how much un-processed time we’ve gathered
    constexpr float fixedTimeStep = 0.75f;          // tick rate (in seconds)
    bool  isRunning = true;


    while (isRunning)
    {
        if (currentScene == Scenes::LEVEL_1
            || currentScene == Scenes::LEVEL_2
            || currentScene == Scenes::LEVEL_3)
        {
            auto   currentTime = Clock::now();
            float  frameTime = std::chrono::duration<float>(currentTime - lastUpdateTime).count(); //how long the last frame took in seconds,
            lastUpdateTime = currentTime;
            timeAccumulator += frameTime;

            player->Update(currentLevel->GetMap(), *player);

            while (timeAccumulator >= fixedTimeStep)
            {
                currentLevel->Update();            // your existing map/AI/physics tick
                timeAccumulator -= fixedTimeStep;  // consume that slice of time
            }

            if(player->GetParty()->IsDefeated())
             {
                delete currentLevel;
                delete player;
                MoveToScene(Scenes::LOSE);
			}

            if (currentLevel->CheckWin())
            {
                switch (currentScene)
                {
                    case LEVEL_1:
					    Ui::PrintLevelTransition();
					    MoveToScene(Scenes::LEVEL_2);
                        break;

                    case LEVEL_2:
					    Ui::PrintLevelTransition();
					    MoveToScene(Scenes::LEVEL_3);
                        break;

                    case LEVEL_3:
                        delete currentLevel;
                        delete player;
					    MoveToScene(Scenes::WIN);
                        break;
              
                    default:
                        break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}


void Game::MoveToScene(Scenes targetScene)
{
    currentScene = targetScene;

    switch (currentScene)
    {
    case LEVEL_1:
		player = new Player(Vector2(0, 0));
        currentLevel = new Level(Scenes::LEVEL_1, *player);
        RunGameLoop();
        break;

    case LEVEL_2:
        delete currentLevel; 
        currentLevel = new Level(Scenes::LEVEL_2, *player);
        player->NewLevel();
        break;

    case LEVEL_3:
        delete currentLevel;
        currentLevel = new Level(Scenes::LEVEL_3, *player);
        player->NewLevel();
        break;

    case OPENING:
	    MoveToScene( Ui::PrintOpeningScreen());
        break;

    case TUTORIAL:
        Ui::Tutorials();
        break;

    case WIN:
        Ui::PrintWinScreen();
        break;

    case LOSE:
        Ui::PrintLoseScreen();
        break;

    default:
        break;
    };
}