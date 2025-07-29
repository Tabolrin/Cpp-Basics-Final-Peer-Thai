#pragma once

#include "Elements.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "UnitInfo.h"

class InfoGenerator
{
private:

    std::unordered_map<Elements, std::vector<std::string>> namePools;
	const std::string fireNamesFile = "FireNames.txt";
    const std::string waterNamesFile = "WaterNames.txt";
    const std::string grassNamesFile = "GrassNames.txt";

    void LoadNamesFromFile(const Elements& element, const std::string& filename);

    void LoadAllFiles();

public:
    InfoGenerator();

   UnitInfo GetRandomEnemyInfo(const int level);

   std::string GetRandomName(const Elements element);

    
  
};
