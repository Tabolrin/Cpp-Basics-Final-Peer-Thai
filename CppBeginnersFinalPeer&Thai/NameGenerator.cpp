#include "NameGenerator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "Elements.h"


void NameGenerator::LoadNamesFromFile(const Elements& element, const std::string& filename)
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

void NameGenerator::LoadAllFiles()
{
    LoadNamesFromFile(Elements::FIRE, "fire_names.txt");
    LoadNamesFromFile(Elements::WATER, "water_names.txt");
    LoadNamesFromFile(Elements::GRASS, "grass_names.txt");
}



NameGenerator::NameGenerator()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once
    LoadAllFiles();
}


std::string NameGenerator::GetRandomName(const Elements element)
{
    auto& pool = namePools[element];

    if (pool.empty())
        return "No more names available.";

    int index = rand() % pool.size();
    std::string selectedName = pool[index];
    pool.erase(pool.begin() + index); // Remove used name

    return selectedName;
}