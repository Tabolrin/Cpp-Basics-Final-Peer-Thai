#include "Map.h"
#include <iostream>

void Map::UpdateFromData(const MapData& data) {
	// Update the visual array from game data
	for (const auto& pair : data.getAllObjects()) {
		const Vector2& pos = pair.first;
		if (!CheckIsPointInMap(pos)) continue;
		GameObject* obj = pair.second;
		char ch = GetCharForObject(obj);
		mapArray[pos.x][pos.y] = ch;
	}
}

void Map::InitialDraw() const {
	// Draw the whole map once at start
	system("cls");
	for (int x = 0; x < height; ++x) {
		for (int y = 0; y < width; ++y) {
			char ch = mapArray[x][y];
			SetConsoleTextAttribute(hConsole, GetColorForChar(ch));
			std::cout << ch;
		}
		std::cout << std::endl;
	}
}

void Map::UpdatePosition(const Vector2& pos, char newChar, int color) {
	// Change only one spot on screen
	COORD coord = { (SHORT)pos.y, (SHORT)pos.x };
	SetConsoleCursorPosition(hConsole, coord);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << newChar;
	mapArray[pos.x][pos.y] = newChar;
}

bool Map::IsTileClear(const Vector2& tile) const {
	return CheckIsPointInMap(tile) && mapArray[tile.x][tile.y] == CLEAR;
}

bool Map::CheckIsPointInMap(const Vector2& point) const {
	return point.x >= 0 && point.x < height && point.y >= 0 && point.y < width;
}

char Map::GetCharForObject(const GameObject* obj) const {
	if (!obj) return CLEAR;
	std::string tag = obj->getTag();
	if (tag == "Player") return PLAYER;
	if (tag == "Enemy") return ENEMY;
	if (tag == "Wall") return WALL;
	if (tag == "Chest") {
		Chest* c = (Chest*)obj;  // Simple cast for beginner
		return c->IsEmpty() ? EMPTY_CHEST : FULL_CHEST;
	}
	if (tag == "Key") return KEY;
	if (tag == "Exit") return EXIT;
	return CLEAR;
}

int Map::GetColorForChar(char ch) const {
	// Pick color based on char
	switch (ch) {
	case ENEMY: return 4;
	case PLAYER: return 11;
	case FULL_CHEST: return 14;
	case EMPTY_CHEST: return 8;
	case EXIT: return 1;
	case KEY: return 5;
	default: return 7;
	}
}