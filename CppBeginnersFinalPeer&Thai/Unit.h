#pragma once
#ifndef _UNIT_
#define _UNIT_
#include <string>
#include "GameObject.h"
#include "Elements.h"
#include "Map.h"
#include "Player.h"

using namespace std;

class Unit : public GameObject
{
protected:
	int maxHp;
	int hp;
	int normalDmg;
	int elementalDmg;
	Elements element;

public:
	Unit(int maxHp, int normalDmg, int elementalDmg, Elements element, const Vector2& location);
};
#endif