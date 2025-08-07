#include "Colors.h"
#include "Scenes.h"
#include "Map.h"
#include "Symbols.h"
#include "Ui.h"
#include <iostream>


Map::Map(Scenes level)
{
	this->level = level;
	// Initialize map with default size
	/*switch (level)
	{
		case Scenes::LEVEL_1:
			Initialize(20, 20);
			break;
		case  Scenes::LEVEL_2:
			Initialize(30, 30);
			break;
		case  Scenes::LEVEL_3:
			Initialize(40, 40);
			break;
		default:
			Initialize(20, 20);
			break;
	}*/ //todo: delete?
}

void Map::Initialize(int w, int h)
{
	width = w;
	height = h;
	mapMat.clear();
	mapMat.resize(height, std::string(width, Symbols::CLEAR));
}

void Map::UpdatePosition(const Vector2& pos, char newChar, int color)
{
	COORD coord = { (SHORT)pos.y, (SHORT)pos.x };
	SetConsoleCursorPosition(hConsole, coord);
	SetConsoleTextAttribute(hConsole, Ui::GetColorForChar(newChar));
	std::cout << newChar;
	mapMat[pos.x][pos.y] = newChar;
}

bool Map::IsTileClear(const Vector2& tile) const
{
	return CheckIsPointInMap(tile) && mapMat[tile.x][tile.y] == Symbols::CLEAR;
}

Symbols Map::GetCharAt(Vector2& pos)
{
	if (CheckIsPointInMap(pos))
		return (static_cast<Symbols>(mapMat[pos.x][pos.y]));
	else 
		return Symbols::INVALID; 
}

bool Map::CheckIsPointInMap(const Vector2& point) const
{
	return point.x >= 0 && point.x < height && point.y >= 0 && point.y < width;
}