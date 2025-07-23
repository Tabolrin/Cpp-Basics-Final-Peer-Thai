#pragma once
#ifndef _PLAYER_
#define _PLAYER_
#include "GameObject.h"
#include "Map.h"
#include "Colors.h"
static const char PLAYER_SYMBOL = '¡';
class Player : public GameObject
{
	Colors playerColor = Colors::DARK_CYAN;
	int speed = 1;
	char upButton = 'w';
	char downButton = 's';
	char leftButton = 'a';
	char rightButton = 'd';
public:
	Player(const Vector2& location);
	void Move(Map map, Vector2& direction);
	void Update(Map map) override;
};
#endif