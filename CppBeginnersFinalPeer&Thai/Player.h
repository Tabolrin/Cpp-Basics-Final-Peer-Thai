#pragma once
#ifndef _PLAYER_
#define _PLAYER_
#include "GameObject.h"
static const char PLAYER_SYMBOL = '¡';

class Player : public GameObject
{
public:
	Player(const Vector2& location);
	void Move(Vector2& direction);
	void Update() override;
};
#endif