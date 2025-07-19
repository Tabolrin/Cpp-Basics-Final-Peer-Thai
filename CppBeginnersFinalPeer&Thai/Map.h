#pragma once
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "GameObject.h"
using namespace std;

enum class MapType
{
	MAP_LEVEL1 = 1,
	MAP_LEVEL2 = 2,
	MAP_LEVEL3 = 3,
};

class Map
{
	public:
	MapType mapType;

	unordered_map<Vector2, GameObject> mapData;

	Map(MapType type) : mapType(type) {}
};

