#pragma once
#include "GameObject.h"

class Chest : public GameObject {
	bool empty = false;
public:
	Chest(const Vector2& loc) : GameObject(loc) { setTag("Chest"); }
	void update() override {}
	void Interact() { empty = true; }
	bool IsEmpty() const { return empty; }
};