#pragma once
#include "Map.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>

class Level {
private:
    Map map;
    Unit& player;
    Vector2 keyLocation;
    bool playerAtExit;
    int enemyDamageMultiplier;
    int enemyHPMultiplier;
    std::vector<GameObject> chests;
    std::vector<Enemy> enemies;

public:
    static Vector2 SpawnLocation;

    Level(MapData::MapType currentLevel, Player& player);
    void ReadyInteractionLists();
    void EnemyScanSequence(Unit& player);
    bool InitiateCombatSequence(Map& map, Unit& player, Unit& enemy);
    Unit FindEnemyAt(const Vector2& enemyLocation);
    bool IsOnTrap();
    //std::vector<SingleUseObject>& GetSingleUseObjectCollection(SingleUseObject::SingleUseObjectType type);
    bool IsLevelWon(const Unit& player);
    Map& GetCurrentMap();
    Vector2 GetKeyLocation() const;
    void PlacePlayerAtSpawn();
   // SingleUseObject FindChestByLocation(const Vector2& location);
    void SetPlayerAtExit(bool value);

private:
    void PerformAttack(Unit& attacker, Unit& target);
};
