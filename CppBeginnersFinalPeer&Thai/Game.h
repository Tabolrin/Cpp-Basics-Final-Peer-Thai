#pragma once

#include "Level.h"
#include "Player.h"
#include "Scenes.h"

class Game 
{
public:
	Game();
	 void RunGameLoop();
	 void MoveToScene(Scenes targetScene);

private:
	 Scenes currentScene;
	 Level* currentLevel;
	 Player* player;
};