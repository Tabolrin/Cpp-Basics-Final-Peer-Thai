#include "InfoGenerator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "Elements.h"

#define ELEMENT_AMOUNT 3

void InfoGenerator::LoadNamesFromFile(const Elements& element, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::vector<std::string> names;

    while (std::getline(file, line))
    {
        if (!line.empty())
            names.push_back(line);
    }

    namePools[element] = names;
}

void InfoGenerator::LoadAllFiles()
{
    LoadNamesFromFile(Elements::FIRE, "FireNames.txt");
    LoadNamesFromFile(Elements::WATER, "WaterNames.txt");
    LoadNamesFromFile(Elements::GRASS, "GrassNames.txt");
}



InfoGenerator::InfoGenerator()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once
    LoadAllFiles();
}


UnitInfo InfoGenerator::GetRandomEnemyInfo(const int level)
{
    UnitInfo info;

    info.level = level;
    info.maxHp = 10 + level * 10;
    info.normalDmg = 5 + level;
    info.elementalDmg = 3 + level; 
    info.element = static_cast<Elements>(rand() % ELEMENT_AMOUNT);

    // Get a random name from the corresponding pool
    if (namePools.find(info.element) == namePools.end() || namePools[info.element].empty())
    {
        std::cerr << "No names available for element: " << static_cast<int>(info.element) << std::endl;
        info.name = "Unknown";
        return info;
	}

    info.name = GetRandomName(info.element);
	return info;
}

std::string InfoGenerator::GetRandomName(const Elements element)
{
    auto& pool = namePools[element];

    if (pool.empty())
        return "No more names available.";

    int index = rand() % pool.size();
    std::string selectedName = pool[index];
    pool.erase(pool.begin() + index); 

    return selectedName;
}