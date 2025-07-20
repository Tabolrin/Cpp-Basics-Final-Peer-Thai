#include "Unit.h"
#include <windows.h>

Unit::Unit(int maxHp, int normalDmg, int elementalDmg, string element, const Vector2<int>& location) : GameObject(location) {}