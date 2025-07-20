#pragma once
#include "Unit.h"
#include <windows.h>

static const char ENEMY_SYMBOL =  'ö';

class Enemy : public Unit
{
public:
	Enemy(int maxHp, int normalDmg, int elementalDmg, string element, const Vector2<int>& location);
	void AddPatrolPoint(COORD point);
	void Patrol();
	void FollowPlayer();
};

