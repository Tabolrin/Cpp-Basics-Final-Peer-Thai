#include "Unit.h"
#include <windows.h>

Unit::Unit(std::string nameIn, int maxHpIn, int normalDmgIn, int elementalDmgIn, Elements elementIn, const Vector2& location) : GameObject(location)
{
	name = nameIn;
	maxHp = maxHpIn;
	hp = maxHp;
	elementalDmg = elementalDmgIn;
	normalDmg = normalDmgIn;
	element = elementIn;
}

void Unit::PlayerLevelUp()
{
	maxHp += 10;
	hp = maxHp;
	normalDmg += 3;
	elementalDmg += 2;
}

HitResult Unit::HitOrMiss() const 
{
	int roll = rand() % 100;

	if (roll < 3)       // 3% chance to critically miss
		return HitResult::MISS;

	if (roll > 97)      // 2% chance to critically hit
		return HitResult::CRIT;

	if (roll < 85)      // 85% normal hit
		return HitResult::HIT;

	return HitResult::MISS;
}

void Unit::EnemyLevelUp()
{
	maxHp += 5;
	normalDmg += 2;
	elementalDmg += 1;
}


void Unit::TakeDamage(int damage)
{
	hp -= damage;
	if (hp < 0)
		hp = 0;
}

void Unit::Heal(int amount)
{
	hp += amount;
	if (hp > maxHp)
		hp = maxHp;
}

void Unit::Attack(Unit* target)
{
	if (target)
	{
		int damage = normalDmg + elementalDmg; // Combine normal and elemental damage
		target->TakeDamage(damage);
	}
}


std::string Unit::GetElementString() const
{
	switch (element)
	{
	case Elements::FIRE:
		return "Fire";
	case Elements::WATER:
		return "Water";
	case Elements::GRASS:
		return "Grass";
	default:
		return "Unknown";
	}
}