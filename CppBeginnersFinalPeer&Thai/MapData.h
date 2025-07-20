#pragma once
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "GameObject.h"
using namespace std;



class MapData
{
public:
	enum class MapType
	{
		MAP_LEVEL1 = 1,
		MAP_LEVEL2 = 2,
		MAP_LEVEL3 = 3,
	};


	MapData(MapType type) : mapType(type) {}

	void addGameObject(const Vector2<int>& position, const GameObject& gameObject)
	{
		mapData[position] = gameObject;
	}

	void removeGameObject(const Vector2<int>& position)
	{
		mapData.erase(position);
	}

	GameObject* getGameObject(const Vector2<int>& position)
	{
		auto it = mapData.find(position);

		if (it != mapData.end())
			return &it->second;

		return nullptr;
	}

	MapType getMapType() const { return mapType; }

protected:
	MapType mapType;

	unordered_map<Vector2<int>, GameObject> mapData;
};

