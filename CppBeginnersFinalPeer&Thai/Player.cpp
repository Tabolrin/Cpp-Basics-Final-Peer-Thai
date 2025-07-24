#include "Inventory.h" 
#include "Player.h"
#include "Ui.h"
#include <conio.h> 
#include <iostream>

Player::Player(const Vector2& pos) : GameObject(position)
{
	position = pos;
	keyAcquired = false;
        // inventory managed as a member; no need for dynamic allocation
}

void Player::Move(Map& map, Vector2& direction)
{
	bool isDirectionValid = false;
	Vector2 tempPos = position + direction;

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
				inventory.AddItem(Items::LEVEL_KEY);
				break;
			}


			case Symbols::FULL_CHEST:
			{
				break;
			}
		}
	}

}

void Player::Update(Map& map)
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