#include "Inventory.h" 
#include "Player.h"
#include "Ui.h"
#include <conio.h> 
#include <iostream>

Player::Player(const Vector2& pos) : GameObject(position)
{
	position = pos;
	keyAcquired = false;
	inventory = new Inventory();
	party = new PlayerParty();
}


void Player::Move(Map map, Vector2& direction)
{
	bool isDirectionValid = false;
	Vector2 tempPos = position + direction;
	// TODO: Check if the new position is within the bounds of the map and make sure player cant step on a chest (discuss with Thai
	if (map.GetCharAt(tempPos) == Symbols::CLEAR || map.GetCharAt(tempPos) == Symbols::FULL_CHEST
		|| map.GetCharAt(tempPos) == Symbols::KEY)
	{
		map.UpdatePosition(position, Symbols::CLEAR, Ui::GetColorForChar(Symbols::PLAYER));
		position = tempPos;
		map.UpdatePosition(position, Symbols::PLAYER, Ui::GetColorForChar(Symbols::CLEAR));

		switch (map.GetCharAt(tempPos))
		{
			case Symbols::KEY:
			{
				keyAcquired = true;
				(*inventory).AddItem(Items::LEVEL_KEY);
				break;
			}

			case Symbols::FULL_CHEST:
			{
				// Random item (HP_POTION..SMOKE_BOMB)
				Items randomItem = static_cast<Items>(rand() % 4);
				inventory->AddItem(randomItem);
				std::cout << "You found item #" << static_cast<int>(randomItem) << "!\n";

				// Turn chest to empty
				map.UpdatePosition(position, Symbols::EMPTY_CHEST, Ui::GetColorForChar(Symbols::EMPTY_CHEST));
				break;
			}
		}
	}

}

void Player:: Update(Map map, Player player)
{
	Vector2 direction = Vector2 (0,0);
	char playerInput;

	if (_kbhit())
	{
		playerInput = _getch();

		if (playerInput == upButton || playerInput == upButton - 32)
		{
			direction.x -= speed;
		}
		
		if (playerInput == downButton || playerInput == downButton - 32)
		{
			direction.x += speed;
		}

		if (playerInput == leftButton || playerInput == leftButton - 32)
		{
			direction.y -= speed;
		}

		if (playerInput == rightButton || playerInput == rightButton - 32)
		{
			direction.y += speed;
		}

		Move(map, direction);
	}
}

bool Player::IsKeyAcquired()
{
	return keyAcquired;
}

void Player::NewLevel()
{
	keyAcquired = false;
}

Vector2 Player::GetPlayerPos()
{
	return position;
}

Player::~Player()
{

}
