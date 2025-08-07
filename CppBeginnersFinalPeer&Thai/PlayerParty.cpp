#include "PlayerParty.h"
#include "InfoGenerator.h"
#include "Elements.h"

PlayerParty::PlayerParty()
{
	InfoGenerator nameGen;
	Vector2 partyMemberPosition(-1, -1); // Placeholder position
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::FIRE), 100, 15, 20, Elements::FIRE, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::WATER), 80, 17, 17, Elements::WATER, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::GRASS), 90, 22, 18, Elements::GRASS, partyMemberPosition);
	//todo: delete at end, emplace_back(...): directly constructs a new element at the end of the container
	// by forwarding the given arguments to its constructor—no temporary object,
	// copy, or move is needed. DELETE
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