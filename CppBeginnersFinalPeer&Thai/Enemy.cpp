#include "CombatSystem.h"
#include "Elements.h"
#include "Enemy.h"
#include "InfoGenerator.h"
#include "Player.h"
#include "Ui.h"
#include "UnitInfo.h"
#include <cmath>
#include <string>
#include <windows.h>

#define REACTION_RANGE 4
#define BATTLE_RANGE 1

Enemy::Enemy(int level, const Vector2& location) : Unit(position)
{
    InfoGenerator infoGen;
    UnitInfo info = infoGen.GetRandomEnemyInfo(level);
    name = info.name;
	level = info.level;
    maxHp = info.maxHp;
    hp = info.maxHp;
    normalDmg = info.normalDmg;
    elementalDmg = info.elementalDmg;
    element = info.element;
    position = location;

    speed = 1; 
	currentPoint = 0;
}

void Enemy::AddPatrolPoint(Map& map, Vector2 point)
{
    if (IsPointValid(map, point))
        patrolRoute.push_back(point);
    else
		std::cout << "Invalid patrol point: " << point.x << ", " << point.y << std::endl;
}

void Enemy::Patrol(Map& map)
{
    GoToPoint(map, patrolRoute.at(currentPoint));

    if (position == patrolRoute.at(currentPoint))
    {
        ++currentPoint;

        if (currentPoint >= patrolRoute.size())
            currentPoint = 0;
    }
}

void Enemy::GoToPoint(Map& map, Vector2& point)
{
    Vector2 nextPos;

    if ((position).x < point.x)
    {
        nextPos.x = (position).x + speed;
        nextPos.y = (position).y;

        if (IsPointValid(map, nextPos))
        {
            map.UpdatePosition(nextPos, Symbols::ENEMY); 
            map.UpdatePosition(position, Symbols::CLEAR);
            position = nextPos;
            return;
        }
    }

    else if ((position).x > point.x)
    {
        nextPos.x = (position).x - speed;
        nextPos.y = (position).y;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    if ((position).y < point.y)
    {
        nextPos.x = (position).x;
        nextPos.y = (position).y + speed;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    else if ((position).y > point.y)
    {
        nextPos.x = (position).x;
        nextPos.y = (position).y - speed;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    return;
}

bool Enemy::IsPointValid(Map& map, Vector2& point)
{
    if (map.CheckIsPointInMap(point))
        if (map.GetCharAt(point) == Symbols::CLEAR)
            return true;

    return false;
}

void Enemy::ChangePosition(Map& map, Vector2& nextPos)
{
    map.UpdatePosition(nextPos, Symbols::ENEMY); //move enemy char to new position

    map.UpdatePosition((position), Symbols::CLEAR);//delete enemy char from old position

    (position) = nextPos;
    return;
}

void Enemy::Update(Map& map, Player& player)
{
	Vector2 playerPos = player.GetPlayerPos();

    if (IsInRange(playerPos, REACTION_RANGE))
    {
        if (!IsInRange(playerPos, BATTLE_RANGE))
            GoToPoint(map, playerPos);
        else
        {
            if (hp > 0)
            {
                player.InCombat = true;
                CombatSystem::Combat(player, *this, *player.GetInventory());
            }
            else
            {
				player.InCombat = false; // end combat if enemy is defeated

                system("cls");
                map.UpdatePosition(position, Symbols::CLEAR); // clear enemy position
                return; 
			}
        }
    }
    else
        Patrol(map);
}

bool Enemy::IsInRange(const Vector2& targetPosition, int range)
{
    if (abs((position).x - targetPosition.x) <= range && (abs((position).y - targetPosition.y) <= range ))
        return true;

    return false;
}
