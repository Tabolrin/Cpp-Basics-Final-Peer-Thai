#pragma once
#include "Level.h"
#include "Player.h"

class Game {
public:
	Game();
	void RunGameLoop();
private:
	Level* currentLevel;
	Player* player;
};