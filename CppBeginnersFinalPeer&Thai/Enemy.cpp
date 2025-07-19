#include "Enemy.h"
#include <string>
#include <windows.h>

using namespace std;

Enemy::Enemy(int maxHp, int normalDmg, int elementalDmg, string element) : Unit (maxHp, normalDmg, elementalDmg, element) {}

void Enemy::AddPatrolPoint(COORD point)
{

}

void Enemy::Patrol()
{
    
}
