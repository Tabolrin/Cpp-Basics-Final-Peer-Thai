#pragma once
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <string>
#include "Vector2.h"
#include "Map.h"


// Abstract base class for game objects
class GameObject
{
protected:
	std::string tag;
	Vector2 position;

public:
	GameObject(const Vector2& location) : tag(tag), position(location) {}

	virtual void Update(Map map) = 0;

	virtual ~GameObject() {}

	std::string getTag() const { return tag; }

	Vector2 getPosition() const { return position; }

	void setPosition(const Vector2& newLocation) { position = newLocation; }

	void setTag(const std::string& newTag) { tag = newTag; }
};
#endif