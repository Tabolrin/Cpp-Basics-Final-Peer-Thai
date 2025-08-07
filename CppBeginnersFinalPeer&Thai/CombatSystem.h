#pragma once

#include "PlayerParty.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Unit.h"

class CombatSystem
{
public:
    static bool Combat(PlayerParty& party, Enemy& enemy, Inventory& inventory);

private:
    static Unit* ChoosePartyUnit(PlayerParty& party);
    static void UseItemMenu(Inventory& inventory, Unit* target);
};
