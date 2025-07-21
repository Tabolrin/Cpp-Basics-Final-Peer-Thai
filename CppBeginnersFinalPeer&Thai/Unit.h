#pragma once
#ifndef _UNIT_
#define _UNIT_
#include <string>
#include "GameObject.h"

using namespace std;

class Unit abstract : public GameObject
{
protected:
	int maxHp;
	int hp;
	int normalDmg;
	int elementalDmg;
	string element;

public:
	Unit(int maxHp, int normalDmg, int elementalDmg, string element, const Vector2& location);
};
#endif