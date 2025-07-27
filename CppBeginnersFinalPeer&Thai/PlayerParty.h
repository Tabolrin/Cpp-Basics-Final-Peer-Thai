#pragma once

#include <vector>
#include "Unit.h"
#include <iostream>

class PlayerParty
{
private:
	std::vector<Unit> partyMembers;

public:
	PlayerParty();

	void PrintParty() const;

	std::vector<Unit>& GetAll();

	bool IsDefeated() const;

};
