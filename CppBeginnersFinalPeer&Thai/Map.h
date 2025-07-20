#pragma once
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "GameObject.h"
#include"MapData.h"
#include "Unit.h"



class Map
{
private:
	std::vector<std::vector<char>> mapArray;
	std::vector<std::string> filePaths;
	void SetFilePaths();


public:
    static const char CLEAR = ' ';
    static const char WALL = '▒';
    static const char PLAYER = '¡';
    static const char ENEMY = 'ö';
    static const char FULL_CHEST = 'O';
    static const char EMPTY_CHEST = 'Ø';
    static const char EXIT = 'E';
    static const char KEY = '¬';

    Map(MapData::MapType level);
    void PrintMap() const;
    void MoveObject(GameObject& object, const Vector2& target);
    bool CheckIsPointInMap(const Vector2& point) const;
    void PlaceSignOnMap(char sign, const Vector2& target);
    bool IsTileClear(const Vector2& tile) const; 
    std::vector<std::vector<char>> GetMapArray() const;
};

