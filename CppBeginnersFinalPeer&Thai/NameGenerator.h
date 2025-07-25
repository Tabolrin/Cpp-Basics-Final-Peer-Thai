#pragma once

#include "Elements.h"
#include <string>
#include <unordered_map>
#include <vector>

class NameGenerator
{
private:
    std::unordered_map<Elements, std::vector<std::string>> namePools;
	const std::string fireNamesFile = "FireNames.txt";
    const std::string waterNamesFile = "WaterNames.txt";
    const std::string grassNamesFile = "GrassNames.txt";

    void LoadNamesFromFile(const Elements& element, const std::string& filename);

    void LoadAllFiles();

public:
    NameGenerator();

    std::string GetRandomName(const Elements element);
  
};
