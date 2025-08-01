#pragma once
#include "Elements.h"
#include <string>

struct UnitInfo
{
public:
	std::string name;
	int level = 1;
	int exp = 0;
	int maxHp = 0;
	int normalDmg = 0;
	int elementalDmg = 0;
	Elements element = Elements::FIRE;

	UnitInfo() {}

	UnitInfo(std::string name,int level, int maxHp, int normalDmg, int elementalDmg, Elements element)
		: name(std::move(name)),level(level), maxHp(maxHp), normalDmg(normalDmg), elementalDmg(elementalDmg), element(element){	}
};