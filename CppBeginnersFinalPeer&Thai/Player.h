#pragma once
#include "GameObject.h"
static const char PLAYER_SYMBOL = '¡';

class Player : public GameObject
{ 
public:
	Player(const Vector2& location);
	void Move(Vector2 & direction);


};

