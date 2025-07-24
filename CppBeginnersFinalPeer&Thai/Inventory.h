#pragma once
#ifndef  _INVENTORY_
#define _INVENTORY_

#include <unordered_map>
#include <string>
#include "Items.h"

class Inventory
{
private:
	std::unordered_map<Items, int> inventory;
	bool IsInInventory(Items item);
public:
	Inventory();
	void AddItem(Items item);
	void UseItem(Items item);
};

#endif

