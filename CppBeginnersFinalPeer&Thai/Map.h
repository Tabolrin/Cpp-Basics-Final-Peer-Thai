#pragma once
#ifndef _MAP_
#define _MAP_
#include <vector>
#include "Levels.h"
#include <string>
#include "Vector2.h"
#include <windows.h>



class Map
{
private:
	Levels level;
	std::vector<std::vector<char>> mapMat;
	int width = 0, height = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	static const char CLEAR = ' ';
	static const char WALL = '#';
	static const char PLAYER = '¡';
	static const char ENEMY = 'ö';
	static const char FULL_CHEST = 'O';
	static const char EMPTY_CHEST = 'Ø';
	static const char EXIT = 'E';
	static const char KEY = '¬';

	Map(Levels level);

	std::vector<std::vector<char>> GetMapMatrix() { return mapMat; }

	int GetWidth() const { return width; }

	int GetHeight() const { return height; }

	void Initialize(int w, int h) { width = w; height = h; mapMat.assign(h, std::vector<char>(w, CLEAR)); }

	void UpdatePosition(const Vector2& pos, char newChar, int color);

	bool IsTileClear(const Vector2& tile) const;

	bool CheckIsPointInMap(const Vector2& point) const;

	int GetColorForChar(char ch) const;
};
#endif