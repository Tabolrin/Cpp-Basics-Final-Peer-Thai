#include "Level.h"
#include "Ui.h"
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>

Level::Level(int num, Player& p) : data(static_cast<MapData::MapType>(num)), player(p), levelNum(num) {
	// Pick file based on level
	switch (num) {
	case 1: filePath = "Map1.txt"; break;
	case 2: filePath = "Map2.txt"; break;
	case 3: filePath = "Map3.txt"; break;
	}
	LoadMapFile();
	map.Initialize(mapWidth, mapHeight);
	map.UpdateFromData(data);
	Ui::PrintFrame(*this, data.getMapType(), player);
}

void Level::LoadMapFile() {
	std::ifstream file(filePath);
	if (!file) return;
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(file, line)) {
		lines.push_back(line);
		mapWidth = std::max(mapWidth, static_cast<int>(line.length()));
	}
	mapHeight = lines.size();
	for (int x = 0; x < mapHeight; ++x) {
		for (int y = 0; y < lines[x].length(); ++y) {
			char ch = lines[x][y];
			Vector2 pos(x, y);
			PopulateObjects(ch, pos);
		}
		for (int y = lines[x].length(); y < mapWidth; ++y) {
			PopulateObjects(CLEAR, Vector2(x, y));
		}
	}
}

void Level::PopulateObjects(char ch, const Vector2& pos) {
	// Create objects from map char
	GameObject* obj = nullptr;
	if (ch == WALL) obj = new Wall(pos);
	else if (ch == FULL_CHEST) obj = new Chest(pos);
	else if (ch == KEY) { obj = new Key(pos); keyLocation = pos; }
	else if (ch == EXIT) obj = new Exit(pos);
	else if (ch == ENEMY) {
		Enemy* e = new Enemy(50, 10, 5, "fire", pos);
		obj = e;
		enemies.push_back(e);
	}
	else if (ch == PLAYER) {
		player.setPosition(pos);
		obj = &player;
	}
	if (obj) data.addGameObject(pos, obj);
}

void Level::Update() {
	map.UpdateFromData(data);
}

bool Level::CheckWin() {
	if (player.getPosition() == data.getGameObject(keyLocation)->getPosition()) {
		Ui::AddToLog("Key collected!");
	}
	if (player.getPosition() == data.getGameObject(EXIT)->getPosition() && keyLocation.x != -1) {
		playerAtExit = true;
	}
	return playerAtExit;
}

void Level::TransitionToNext() {
	system("cls");
	std::cout << "Transition to Level " << (levelNum + 1) << "!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Level::MovePlayer(const Vector2& dir) {
	Vector2 oldPos = player.getPosition();
	Vector2 newPos = oldPos + dir;
	if (map.IsTileClear(newPos)) {
		data.removeGameObject(oldPos);
		player.setPosition(newPos);
		data.addGameObject(newPos, &player);
		char oldCh = map.CLEAR;
		int oldColor = map.GetColorForChar(oldCh);
		map.UpdatePosition(oldPos, oldCh, oldColor);
		char newCh = map.GetCharForObject(&player);
		int newColor = map.GetColorForChar(newCh);
		map.UpdatePosition(newPos, newCh, newColor);
	}
}

void Level::UpdateEnemies() {
	for (auto* e : enemies) {
		Vector2 dir(0, 1);
	}
}

void Level::InitiateCombat(Unit& p, Unit& e) {
	Ui::AddToLog("Combat!");
}