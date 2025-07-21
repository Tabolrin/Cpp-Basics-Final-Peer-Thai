#include "Map.h"
#include "Levels.h"
#include "Symbols.h"
#include "Colors.h"
#include <iostream>

/*void Map::Update(Vector2 pos1, Vector2 pos2)
{
		const Vector2& pos = pair.first;

		if (!CheckIsPointInMap(pos))
			continue;

		GameObject* obj = pair.second;
		char ch = GetCharForObject(obj);
		mapArray[pos.x][pos.y] = ch;
	}
}*/

Map::Map(Levels level)
{
	this->level = level;
	// Initialize map with default size
	switch (level)
	{
	case Levels::MAP_LEVEL1:
		Initialize(20, 20);
		break;
	case  Levels::MAP_LEVEL2:
		Initialize(30, 30);
		break;
	case  Levels::MAP_LEVEL3:
		Initialize(40, 40);
		break;
	default:
		Initialize(20, 20);
		break;
	}
}

void Map::Initialize(int w, int h)
{
	width = w;
	height = h;
	mapMat.clear();
	mapMat.resize(height, std::vector<char>(width));
}

void Map::UpdatePosition(const Vector2& pos, char newChar, int color)
{
	// Change only one spot on screen
	COORD coord = { (SHORT)pos.y, (SHORT)pos.x };
	SetConsoleCursorPosition(hConsole, coord);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << newChar;
	mapMat[pos.x][pos.y] = newChar;
}

bool Map::IsTileClear(const Vector2& tile) const
{
	return CheckIsPointInMap(tile) && mapMat[tile.x][tile.y] == Symbols::CLEAR;
}

bool Map::CheckIsPointInMap(const Vector2& point) const
{
	return point.x >= 0 && point.x < height && point.y >= 0 && point.y < width;
}


int Map::GetColorForChar(char ch) const
{
	// Pick color based on char
	switch (ch) 
	{
	case ENEMY:
		return static_cast<int>(Colors::DARK_RED);
		break;

	case PLAYER:
		return static_cast<int>(Colors::DARK_CYAN);
		break;

	case FULL_CHEST:
		return static_cast<int>(Colors::LIGHT_YELLOW);
		break;

	case EMPTY_CHEST:
		return static_cast<int>(Colors::GRAY);
		break;

	case EXIT: 
		return static_cast<int>(Colors::DARK_BLUE);
		break;

	case KEY:
		return static_cast<int>(Colors::MAGENTA);
		break;

	default:
		return static_cast<int>(Colors::BRIGHT_WHITE);
		break;
	}
}