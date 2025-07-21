#pragma once
#include "GameObject.h"

class Exit : public GameObject {
public:
	Exit(const Vector2& loc) : GameObject(loc) { setTag("Exit"); }
	void update() override {}
};