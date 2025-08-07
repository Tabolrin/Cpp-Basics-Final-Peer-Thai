#include "Inventory.h" 
#include "Items.h"
#include "Player.h"
#include "Ui.h"
#include <conio.h> 
#include <iostream>

Player::Player(const Vector2& pos) : GameObject(position)
{
	position =  pos;
	KeyAcquired = false;
	inventory = new Inventory();
	party = new PlayerParty();
}


void Player::Move(Map& map, Vector2& direction)
{
	bool isDirectionValid = false;
	Vector2 tempPos = position + direction;

	// TODO: Check if the new position is within the bounds of the map and make sure player cant step on a chest (discuss with Thai
	if (map.GetCharAt(tempPos) == Symbols::CLEAR || map.GetCharAt(tempPos) == Symbols::FULL_CHEST
		|| map.GetCharAt(tempPos) == Symbols::KEY || map.GetCharAt(tempPos) == Symbols::EXIT)
	
		map.UpdatePosition(position, Symbols::CLEAR, Ui::GetColorForChar(Symbols::PLAYER));
		position = tempPos;
		map.UpdatePosition(position, Symbols::PLAYER, Ui::GetColorForChar(Symbols::CLEAR));

		switch (map.GetCharAt(tempPos))
		{
			case Symbols::KEY:
			{
				KeyAcquired = true;
				(*inventory).AddItem(Items::LEVEL_KEY);
				break;
			}

			case Symbols::FULL_CHEST:
			{
				// Random item
				Items randomItem = static_cast<Items>(rand() % 4);
				inventory->AddItem(randomItem);
				Ui::PrintNotification(randomItem);

				//todo: delete if gave up on it
				// Turn chest to empty
				map.UpdatePosition(position, Symbols::EMPTY_CHEST, Ui::GetColorForChar(Symbols::EMPTY_CHEST));
				break;
			}

			case Symbols::EXIT:
			{
				if (KeyAcquired)
					IsAtExit = true;
				else
					std::cout << "You need to acquire the key first!\n";
				break;
			}
		}
}


void Player::PickUpChest(Map& map)
{ 
	if (map.GetMapMatrix()[((position).x + 1)][(position).y] == Symbols::FULL_CHEST)
	{
		map.GetMapMatrix()[((position).x + 1)][ (position).y] = Symbols::EMPTY_CHEST;

		Items item = Items::NONE;
		while(item == Items::NONE)
		{
			item = inventory->GetRandomItemFromChest();
		}

		(*inventory).AddItem(item);
	}
}

void Player:: Update(Map& map, Player& player)
{
	Vector2 direction = Vector2 (0,0);
	char playerInput;

	if (_kbhit())// if a key was pressed
	{
		playerInput = _getch();

		// check each movement key (allow lowercase and uppercase)

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

		Move(map, direction);// move the player on the map
	}
}

bool Player::IsKeyAcquired() const
{
	return KeyAcquired;
}

void Player::NewLevel()
{
	KeyAcquired = false;
}

Vector2 Player::GetPlayerPos()
{
	return position;
}

Player::~Player()
{

}
