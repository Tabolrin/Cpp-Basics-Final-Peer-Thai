#include "Player.h"

Player::Player(const Vector2<int>& location) : GameObject(location) {}

void Player::Move(Vector2 <int>& direction)
{
	position += direction;

}
