#pragma once
#include "GameObject.h"

class Key : public GameObject {
public:
	Key(const Vector2& loc) : GameObject(loc) { setTag("Key"); }
	void Update() override {}
};