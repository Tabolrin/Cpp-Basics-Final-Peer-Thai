#pragma once
#ifndef _GAME_
#define _GAME_


#include "Level.h"
#include "Player.h"

class Game 
{
public:
	Game();
	void RunGameLoop();
private:
	Level* currentLevel;
	Player* player;
};

#endif