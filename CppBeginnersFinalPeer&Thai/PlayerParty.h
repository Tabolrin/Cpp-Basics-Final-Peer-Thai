#pragma once

#include <vector>
#include "Unit.h"
#include <iostream>

class PlayerParty
{
	std::vector<Unit> partyMembers;

public:
	PlayerParty()
	{
		partyMembers.emplace_back("Fire Warrior", 100, 20, Elements::FIRE, Vector2(0, 0));
		partyMembers.emplace_back("Water Mage", 80, 15, Elements::WATER, Vector2(1, 0));
		partyMembers.emplace_back("Grass Druid", 90, 18, Elements::GRASS, Vector2(2, 0));
	}

	void PrintParty() const
	{
		for (const auto& member : partyMembers)
		{
			std::cout << member.GetName()
				<< ", Element: " << member.GetElementString()
				<< ", Level: " << member.GetLevel()
				<< ", HP: " << member.GetHp() << "/" << member.GetMaxHp()
				<< std::endl;
		}
	}

	std::vector<Unit>& GetAll()
	{
		return partyMembers;
	}

	bool IsDefeated() const
	{
		for (const auto& member : partyMembers)
		{
			if (member.GetHp() > 0)
				return false;
		}
		return true;
	}
};
