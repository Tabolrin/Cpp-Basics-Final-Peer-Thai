#pragma once

#include "Scenes.h"
#include "Symbols.h"
#include "Vector2.h"
#include <vector>
#include <string>
#include <windows.h>


class Map
{
private:
	Scenes level;
	std::vector<std::string> mapMat;
	int width = 0, height = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	Map() { level = Scenes::LEVEL_1; }

	Map(Scenes level);

	std::vector<std::string> GetMapMatrix() { return mapMat; }

	int GetWidth() const { return width; }

	int GetHeight() const { return height; }

	void Initialize(int w, int h);

	void UpdatePosition(const Vector2& pos, char newChar);

	bool IsTileClear(const Vector2& tile) const;

	Symbols GetCharAt(Vector2& pos);

	bool CheckIsPointInMap(const Vector2& point) const;
};
