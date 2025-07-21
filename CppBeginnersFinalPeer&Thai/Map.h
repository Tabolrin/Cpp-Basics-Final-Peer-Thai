#pragma once
#ifndef _MAP_
#define _MAP_
#include <vector>
#include "Levels.h"
#include <string>
#include "Vector2.h"
#include <windows.h>
#include "Symbols.h"



class Map
{
private:
	Levels level;
	std::vector<std::vector<char>> mapMat;
	int width = 0, height = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	Map() { level = Levels::MAP_LEVEL1; }

	Map(Levels level);

	std::vector<std::vector<char>> GetMapMatrix() { return mapMat; }

	int GetWidth() const { return width; }

	int GetHeight() const { return height; }

	void Initialize(int w, int h);

	void UpdatePosition(const Vector2& pos, char newChar, int color);

	bool IsTileClear(const Vector2& tile) const;

	bool CheckIsPointInMap(const Vector2& point) const;

	int GetColorForChar(char ch) const;
};
#endif