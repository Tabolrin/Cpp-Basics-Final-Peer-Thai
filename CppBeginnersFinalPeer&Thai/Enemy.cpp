#include "Enemy.h"
#include <string>
#include <windows.h>

using namespace std;

Enemy::Enemy(int maxHp, int normalDmg, int elementalDmg, string element, const Vector2& location) : Unit(maxHp, normalDmg, elementalDmg, element, location) {}

void Enemy::AddPatrolPoint(Vector2& point)
{
}

void Enemy::Patrol()
{
}

void Enemy::FollowPlayer(){}