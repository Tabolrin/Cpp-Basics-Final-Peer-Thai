#pragma once
#ifndef  _ENEMY_
#define _ENEMY_


#include "Elements.h"
#include "Player.h"
#include "Unit.h"
#include "Vector2.h"
#include <string>
#include <vector>


class Enemy : public Unit
{
private:

	int speed;
	int currentPoint;
	std::vector<Vector2> patrolRoute;
        void GoToPoint(Map& map, Vector2 point);
        bool IsPointValid(const Map& map, const Vector2& point);
        void ChangePosition(Map& map, const Vector2& nextPos);
        bool IsInRange(Vector2 playerLocation, int range);
public:
	Enemy(int maxHp, int normalDmg, int elementalDmg, Elements element, const Vector2& location);
        void AddPatrolPoint(const Map& map, Vector2 point);
        void Patrol(Map& map);
        void Update(Map& map, const Player& player);
};
#endif 