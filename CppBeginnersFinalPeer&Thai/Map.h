#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
#include "MapData.h"
#include <windows.h>

class Map {
private:
	std::vector<std::vector<char>> mapArray;
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

	Map() {}

	void Initialize(int w, int h) { width = w; height = h; mapArray.assign(h, std::vector<char>(w, CLEAR)); }

	void UpdateFromData(const MapData& data);

	void InitialDraw() const;

	void UpdatePosition(const Vector2& pos, char newChar, int color);

	bool IsTileClear(const Vector2& tile) const;

	bool CheckIsPointInMap(const Vector2& point) const;

	char GetCharForObject(const GameObject* obj) const;

	int GetColorForChar(char ch) const;
};