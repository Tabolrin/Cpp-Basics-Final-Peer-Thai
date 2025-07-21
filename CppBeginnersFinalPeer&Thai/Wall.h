#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall(const Vector2& loc) : GameObject(loc) { setTag("Wall"); }
	void Update() override {}
};