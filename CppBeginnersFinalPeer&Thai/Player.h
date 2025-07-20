#pragma once
#include "GameObject.h"
static const char PLAYER_SYMBOL = '¡';

class Player : public GameObject
{ 
public:
	Player(const Vector2<int>& location);
	void Move(Vector2 <int>& direction);


};

