#include "Unit.h"
#include <windows.h>

Unit::Unit(int maxHpIn, int normalDmgIn, int elementalDmgIn, Elements elementIn, const Vector2& location) : GameObject(location)
{
	maxHp = maxHpIn;
	hp = maxHp;
	elementalDmg = elementalDmgIn;
	normalDmg = normalDmgIn;
	element = elementIn;
}