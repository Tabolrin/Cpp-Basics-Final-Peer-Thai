#pragma once

#include "PlayerParty.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Unit.h"

class CombatSystem
{
public:
    static void Combat(Player& player, Enemy& enemy, Inventory& inventory);

private:
    static Unit* ChoosePartyUnit(PlayerParty& party);
    static void UseItemMenu(Inventory& inventory, Unit* target);
};
