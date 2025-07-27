#pragma once

#include "Map.h"
#include "Vector2.h"
#include <string>


class GameObject
{
protected:
	Vector2 position;

public:
	GameObject(const Vector2& location){	position =  location; }

	virtual ~GameObject() { }

	Vector2 GetPosition() const { return position; }

	void SetPosition(const Vector2& newLocation) { position = newLocation; }
};
