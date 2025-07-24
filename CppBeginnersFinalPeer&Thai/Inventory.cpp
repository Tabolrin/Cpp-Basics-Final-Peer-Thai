#include "Inventory.h"
#include <iostream>
#include <unordered_map>

#include "Items.h"

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
		inventory[item] = 1;
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
