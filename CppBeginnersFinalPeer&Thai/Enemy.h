#pragma once
#include "Elements.h"
#include "Player.h"
#include "Unit.h"
#include "InfoGenerator.h"
#include "Vector2.h"
#include <vector>



class Enemy : public Unit
{
private:
	int speed = 1;
	int currentPoint;
	std::vector<Vector2> patrolRoute;

	void GoToPoint(Map& map, Vector2& point);
	bool IsPointValid(Map& map, Vector2& point);
	void ChangePosition(Map& map, Vector2& nextPos);
	bool IsInRange(const Vector2& playerLocation, int range);
	void Patrol(Map& map);
public:
	Enemy(int level, const Vector2& location, InfoGenerator& infoGen);
	void AddPatrolPoint(Map& map, Vector2 point);
	void Update(Map& map, Player& player);
};
