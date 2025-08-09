#include "FileIO.h"
#include <fstream>
#include <iostream>

std::vector<std::string> FileIO::LoadFileLines(const std::string& filepath) 
{
    std::vector<std::string> lines;
    std::ifstream in(filepath);

    if (!in) 
    {
        std::cerr << "[Error] Could not open file: " << filepath << "\n";
        return lines;
    }

    std::string line;

    while (std::getline(in, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void FileIO::PrintLines(const std::vector<std::string>& lines) 
{
    for (const auto& line : lines) 
        std::cout << line << "\n";
}
