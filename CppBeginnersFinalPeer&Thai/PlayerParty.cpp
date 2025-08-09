#include "PlayerParty.h"
#include "InfoGenerator.h"
#include "Elements.h"

PlayerParty::PlayerParty()
{
	InfoGenerator nameGen;
	Vector2 partyMemberPosition(-1, -1); // Placeholder position
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::FIRE), 30, 7, 8, Elements::FIRE, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::WATER), 27, 8, 6, Elements::WATER, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::GRASS), 25, 10, 5, Elements::GRASS, partyMemberPosition);
	//adding a nnew unit to the end of the party, so the player got 3 units in the party
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