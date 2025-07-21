#pragma once
#ifndef  _ENEMY_
#define _ENEMY_


#include "Unit.h"
#include <windows.h>
#include <string>
#include "Vector2.h"

static const char ENEMY_SYMBOL = 'ö';

class Enemy : public Unit
{
public:
	Enemy(int maxHp, int normalDmg, int elementalDmg, std::string element, const Vector2& location);
	void AddPatrolPoint(Vector2& point);
	void Patrol();
	void FollowPlayer();
};
#endif 