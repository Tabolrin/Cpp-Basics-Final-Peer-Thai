#include "Elements.h"
#include "Enemy.h"
#include <string>
#include <windows.h>
#include "CombatSystem.h"

#define REACTION_RANGE 2
#define BATTLE_RANGE 1

Enemy::Enemy(int maxHp, int normalDmg, int elementalDmg, Elements element, const Vector2& location) :
    Unit(maxHp, normalDmg, elementalDmg, element, location)
{
    currentPoint = 0;
    speed = 1;
}

void Enemy::AddPatrolPoint(Map map, Vector2 point)
{
    if (IsPointValid(map, point))
        patrolRoute.push_back(point);
    else
        int x;
}

void Enemy::Patrol(Map map)
{
    GoToPoint(map, patrolRoute.at(currentPoint));

    if (position == patrolRoute.at(currentPoint))
    {
        ++currentPoint;
        if (currentPoint >= patrolRoute.size())
            currentPoint = 0;
    }
}

void Enemy::GoToPoint(Map map, Vector2 point)
{
    Vector2 nextPos;

    if (position.x < point.x)
    {
        nextPos.x = position.x + speed;
        nextPos.y = position.y;

        if (IsPointValid(map, nextPos))
        {
            map.UpdatePosition(nextPos, Symbols::ENEMY,
                map.GetCharAt(nextPos) == Symbols::ENEMY); //move enemy char to new position
            map.UpdatePosition(position, Symbols::CLEAR,
                map.GetCharAt(nextPos) == Symbols::CLEAR);//delete enemy char from old position
            position = nextPos;
            return;
        }
    }

    else if (position.x > point.x)
    {
        nextPos.x = position.x - speed;
        nextPos.y = position.y;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    if (position.y < point.y)
    {
        nextPos.x = position.x;
        nextPos.y = position.y + speed;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    else if (position.y > point.y)
    {
        nextPos.x = position.x;
        nextPos.y = position.y - speed;

        if (IsPointValid(map, nextPos))
        {
            ChangePosition(map, nextPos);
            return;
        }
    }

    return;
}

bool Enemy::IsPointValid(Map map, Vector2 point)
{
    if (map.CheckIsPointInMap(point))
        if (map.GetCharAt(point) == Symbols::CLEAR)
            return true;
    return false;
}

void Enemy::ChangePosition(Map map, Vector2 nextPos)
{
    map.UpdatePosition(nextPos, Symbols::ENEMY,
        map.GetCharAt(nextPos) == Symbols::ENEMY); //move enemy char to new position

    map.UpdatePosition(position, Symbols::CLEAR,
        map.GetCharAt(nextPos) == Symbols::CLEAR);//delete enemy char from old position

    position = nextPos;
    return;
}

void Enemy::Update(Map& map, Player& player)
{

    if (IsInRange(player.GetPlayerPos(), REACTION_RANGE))
    {
        GoToPoint(map, player.GetPlayerPos());
        if (IsInRange(player.GetPlayerPos(), BATTLE_RANGE))
        {
            CombatSystem::StartCombat(*player.GetParty(), *this, *player.GetInventory());
        } 
    }
    else
        Patrol(map);
}

bool Enemy::IsInRange(Vector2 targetPosition, int range)
{
    /*
    if (((playerLocation.x - position.x >= 0 && playerLocation.x - position.x <= range)
        || (playerLocation.x - position.x < 0 && position.x - playerLocation.x <= range))
        && ((playerLocation.y - position.y >= 0 && playerLocation.y - position.y <= range)
            || (playerLocation.y - position.y < 0 && position.y - playerLocation.y <= range)))
    {
            return true;
    }
    */

    if ((position.x - targetPosition.x <= range || targetPosition.x - position.x <= range)
        && position.y - targetPosition.y <= range || targetPosition.y - position.y <= range)
        return true;
    return false;
}
