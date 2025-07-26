#include "PlayerParty.h"
#include "NameGenerator.h"
#include "Elements.h"

PlayerParty::PlayerParty()
{
	NameGenerator nameGen;
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::FIRE), 100, 20, Elements::FIRE, Vector2(-1, -1));
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::WATER), 80, 15, Elements::WATER, Vector2(-1, -1));
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::GRASS), 90, 18, Elements::GRASS, Vector2(-1, -1));
}

void PlayerParty::PrintParty() const
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

std::vector<Unit>& PlayerParty::GetAll()
{
	return partyMembers;
}

bool PlayerParty::IsDefeated() const
{
	for (const auto& member : partyMembers)
	{
		if (member.GetHp() > 0)
			return false;
	}
	return true;
}