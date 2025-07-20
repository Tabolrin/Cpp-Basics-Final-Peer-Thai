#pragma once
#include "Map.h"
#include "Ui.h"
#include <fstream>
#include <iostream>
#include <windows.h> // For console colors (Windows-specific)

Map::Map(MapType type) 
{
    SetFilePaths();
    std::ifstream file(filePaths[static_cast<int>(type) - 1]);
   
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open map file: " + filePaths[static_cast<int>(type) - 1]);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }
    file.close();

    int rowCount = lines.size();
    mapArray.resize(rowCount);

    for (int row = 0; row < rowCount; ++row)
    {
        mapArray[row].resize(lines[row].length());

        for (size_t col = 0; col < lines[row].length(); ++col) 
        {
            mapArray[row][col] = lines[row][col];
        }
    }
}

void Map::SetFilePaths()
{
    filePaths = 
    {
        "Maps_Level1.txt",
        "Maps_Level2.txt",
        "Maps_Level3.txt",
    };
}

void Map::PrintMap() const 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (const auto& row : mapArray) 
    {
        for (char character : row) 
        {
            switch (character)
            {
                default:
                    SetConsoleTextAttribute(hConsole, 7); // White
                    std::cout << character;
                    break;
                case ENEMY:
                    SetConsoleTextAttribute(hConsole, 4); // Red
                    std::cout << character;
                    break;
                case PLAYER:
                    SetConsoleTextAttribute(hConsole, 11); // Cyan
                    std::cout << character;
                    break;
                case FULL_CHEST:
                    SetConsoleTextAttribute(hConsole, 14); // Yellow
                    std::cout << character;
                    break;
                case EMPTY_CHEST:
                    SetConsoleTextAttribute(hConsole, 8); // DarkGray
                    std::cout << character;
                    break;
                case EXIT:
                    SetConsoleTextAttribute(hConsole, 1); // DarkBlue
                    std::cout << character;
                    break;
                case KEY:
                    SetConsoleTextAttribute(hConsole, 5); // Magenta
                    std::cout << character;
                    break;
            }
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, 7); // Reset to white
}


void Map::MoveObject(GameObject& object, const Vector2<int>& target)
{
    if (!IsTileClear(target)) 
    {
        Ui::AddToLog("cant go there!");
        return;
    }

    mapArray[target.x][target.y] = mapArray[object.getPosition().x][object.getPosition().y];
    mapArray[object.getPosition().x][object.getPosition().y] = CLEAR;
    object.setPosition(target);
}

bool Map::CheckIsPointInMap(const Vector2<int>& point) const 
{
    return point.x >= 0 && point.x < static_cast<int>(mapArray.size()) &&
        point.y >= 0 && point.y < static_cast<int>(mapArray[point.x].size());
}

void Map::PlaceSignOnMap(char sign, const Vector2<int>& target)
{ 
    mapArray[target.x][target.y] = sign; 
}

bool Map::IsTileClear(const Vector2<int>& tile) const 
{ 
    if (mapArray[tile.x][tile.y] != CLEAR) 
    { 
        Ui::AddToLog("Unable to execute command. The tile is occupied.");
        return false;
    }
    return true;
}

std::vector<std::vector<char>> Map::GetMapArray() const 
{
    return mapArray;
}