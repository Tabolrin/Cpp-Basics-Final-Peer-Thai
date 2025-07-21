#include "Player.h"

Player::Player(const Vector2& location) : GameObject(location) {}

void Player::Move(Vector2& direction)
{
	position += direction;
}

void Player:: Update() 
{

}