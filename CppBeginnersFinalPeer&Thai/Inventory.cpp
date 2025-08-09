#include "Inventory.h"
#include "Items.h"
#include <iostream>
#include <unordered_map>

Inventory::Inventory(){}

bool Inventory::IsInInventory(Items item)
{
	auto i = inventory.find(item);

	if (i == inventory.end())
		return false;
	else
		return true;
}

void Inventory::AddItem(Items item)
{
	if (!IsInInventory(item))
		inventory.insert({ item, 1 }); 
	else
	{
		int itemAmount = inventory.at(item);
		inventory[item] = ++itemAmount;
	}
}

void Inventory::UseItem(Items item)
{
	if (IsInInventory(item))
	{
		int itemAmount = inventory.at(item);
		inventory[item] = --itemAmount;

		if (itemAmount == 0)
			inventory.erase(item);
	}
	else
		std::cout << "Item Not In Inventory" << std::endl;
}


Items Inventory::GetRandomItemFromChest() const
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	const int possibleItemCount = 4;

	const Items pool[possibleItemCount] =
	{
		Items::HP_POTION,
		Items::NORMAL_ATTACK_POTION,
		Items::ELEMENTAL_ATTACK_POTION,
		Items::SMOKE_BOMB
	};

	int idx = std::rand() % possibleItemCount;
	return pool[idx];
}