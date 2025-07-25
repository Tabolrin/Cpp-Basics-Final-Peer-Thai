#pragma once
#include <unordered_map>
#include <string>
#include "Items.h"

class Inventory
{
private:
	std::unordered_map<Items, int> inventory;

public:
	Inventory();
	bool IsInInventory(Items item);
	void AddItem(Items item);
	void UseItem(Items item);
};

