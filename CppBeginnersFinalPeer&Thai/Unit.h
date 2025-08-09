#pragma once

#include <string>
#include "GameObject.h"
#include "Elements.h"
#include "HitResult.h"

class Unit : public GameObject
{
protected:
	std::string name;
	int level = 1;
	int exp = 0;
	int maxHp;
	int hp;
	int normalDmg;
	int elementalDmg;
	Elements element;

	void setMaxHp(int maxHp) { this->maxHp = maxHp; }

	void setHp(int hp) { this->hp = hp; }

public:
	Unit(Vector2& location) : GameObject (location) {}

	Unit(std::string name, int maxHp, int normalDmg, int elementalDmg, Elements element, const Vector2& location);

	int GetMaxHp() const { return maxHp; }

	int GetHp() const { return hp; }

	int GetExp() const { return exp; }

	void AddExp(int exp) { this->exp += exp; }

	int GetNormalDmg() const { return normalDmg; }

	int GetElementalDmg() const { return elementalDmg; }

	HitResult HitOrMiss() const; 

	Elements GetElement() const { return element; }

	std::string GetElementString() const;
	
	int GetLevel() const { return level; }

	std::string GetName() const { return name; }

	void IncreaseNormalDmg(int normalDmg)	{this->normalDmg += normalDmg;	}

	void IncreaseElementalDmg(int elementalDmg) { this->elementalDmg += elementalDmg; }

	void PlayerLevelUp();

	//void EnemyLevelUp();

	void TakeDamage(int damage);

	void Heal(int amount);

	void NormalAttack(Unit* target);

	void ElementalAttack(Unit* target);
};
