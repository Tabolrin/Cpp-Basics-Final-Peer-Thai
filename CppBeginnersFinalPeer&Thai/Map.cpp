#include "Colors.h"
#include "Scenes.h"
#include "Map.h"
#include "Symbols.h"
#include "Ui.h"
#include <iostream>


Map::Map(Scenes level)
{
	this->level = level;
}

void Map::Initialize(int w, int h)
{
	width = w;
	height = h;
	mapMat.clear();
	mapMat.resize(height, std::string(width, Symbols::CLEAR));
}

void Map::UpdatePosition(const Vector2& pos, char newChar)
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
	//return point.x >= 0 && point.x < height && point.y >= 0 && point.y < width;
	bool isRightValid = false;
	bool isLeftValid = false;
	bool isUpValid = false;
	bool isDownValid = false;

	if (point.x <= 0 || point.y <= 0)
		return false;
	if (point.x >= height || point.y >= width)
		return false;

	Vector2 tempPos = Vector2 (point.x, point.y);
	for(int i = point.x; i < height; ++i)
	{
		tempPos.x = i;
		if (mapMat[tempPos.x][tempPos.y] == Symbols::WALL)
		{
			isDownValid = true;
			break;
		}
	}

	tempPos = Vector2(point.x, point.y);
	for (int i = point.x; i >= 0; --i)
	{
		tempPos.x = i;
		if (mapMat[tempPos.x][tempPos.y] == Symbols::WALL)
		{
			isUpValid = true;
			break;
		}
	}

	tempPos = Vector2(point.x, point.y);
	for (int i = point.y; i < width; ++i)
	{
		tempPos.y = i;
		if (mapMat[tempPos.x][tempPos.y] == Symbols::WALL)
		{
			isRightValid = true;
			break;
		}
	}

	tempPos = Vector2(point.x, point.y);
	for (int i = point.y; i >= 0; --i)
	{
		tempPos.y = i;
		if (mapMat[tempPos.x][tempPos.y] == Symbols::WALL)
		{
			isLeftValid = true;
			break;
		}
	}

	return(isDownValid && isUpValid && isRightValid && isLeftValid);
}
