#include "PlayerParty.h"
#include "InfoGenerator.h"
#include "Colors.h"
#include "Elements.h"

PlayerParty::PlayerParty()
{
	InfoGenerator nameGen;
	Vector2 partyMemberPosition(-1, -1); // Placeholder position
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::FIRE), 30, 7, 8, Elements::FIRE, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::WATER), 27, 8, 6, Elements::WATER, partyMemberPosition);
	partyMembers.emplace_back(nameGen.GetRandomName(Elements::GRASS), 25, 10, 5, Elements::GRASS, partyMemberPosition);
	//adding a new unit to the end of the party, so the player got 3 units in the party
}

void PlayerParty::PrintParty() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (const auto& member : partyMembers)
	{
		std::cout << member.GetName()	<< ", Element: ";

		switch (member.GetElement())
		{
			case Elements::FIRE:
			SetConsoleTextAttribute(hConsole, Colors::LIGHT_RED);
			break;

			case Elements::WATER:
				SetConsoleTextAttribute(hConsole, Colors::LIGHT_BLUE);
				break;

			case Elements::GRASS:
				SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN);
				break;

		default:
			SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);
			break;
		}

		std::cout << member.GetElementString();
		SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);
		std::cout << ", Level: " << member.GetLevel()	<< ", HP: ";
		SetConsoleTextAttribute(hConsole, Colors::DARK_RED);
		std::cout << member.GetHp() << "/" << member.GetMaxHp() << std::endl;
		SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);
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