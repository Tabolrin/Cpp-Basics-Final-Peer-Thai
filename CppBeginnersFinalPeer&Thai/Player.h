#pragma once
#include "Colors.h"
#include "GameObject.h"
#include "Inventory.h"
#include "Map.h"
#include "PlayerParty.h"

class Player : public GameObject
{
private:
	Colors playerColor = Colors::DARK_CYAN;
	PlayerParty* party;
	Inventory* inventory;
	int speed = 1;
	char upButton = 'w';
	char downButton = 's';
	char leftButton = 'a';
	char rightButton = 'd';


public:
	bool keyAcquired;
	Player(const Vector2& location);
	void Move(Map map, Vector2& direction);
	void Update(Map map, Player player);
	PlayerParty* GetParty() const { return party; }
	Inventory* GetInventory() const { return inventory; }
	bool IsKeyAcquired();
	void NewLevel();
	Vector2 GetPlayerPos();
	~Player();
};