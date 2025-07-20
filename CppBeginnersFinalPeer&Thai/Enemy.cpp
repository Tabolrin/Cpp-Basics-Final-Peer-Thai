#include "Enemy.h"
#include <string>
#include <windows.h>

using namespace std;

Enemy::Enemy(int maxHp, int normalDmg, int elementalDmg, string element, const Vector2<int>& location) : Unit (maxHp, normalDmg, elementalDmg, element, location) {}
 

void Enemy::AddPatrolPoint(COORD point)
{                                                                                                                                                                                                              
    
}

void Enemy::Patrol()
{
    
}
